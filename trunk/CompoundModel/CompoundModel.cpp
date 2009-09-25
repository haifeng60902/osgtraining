#include "CompoundModel.h"

#include "TransGeomNode2VertArray.h"

#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

#define NUM_COPY 128

CompoundModel::CompoundModel()
{
	//создать главный узел
	m_rootNode = new osg::Group;

	//инициализировать корневой узел
	InitNode();

	//добавить текстуру
	AddTexture();


	//добавить шейдер в узел
	AddShader();

	m_rpCompoundUpdateCallback = new CompoundUpdateCallback;

	//создать картинку, содержащую смещения геометрии
	CreateDynamicImage();

	m_rootNode->setUpdateCallback( m_rpCompoundUpdateCallback.get() );

	// определение ограничивающего объема, размер земли 1024км(в 1 км - 1024 метра), максимальная высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 20 * 128 , 20 , 50 );
	m_rootNode->setInitialBound( bbox );

	//динамический узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

CompoundModel::~CompoundModel()
{

}

void CompoundModel::InitNode()
{
//инициализировать корневой узел
	//загрузить модель
	//flt_optimize/09/255-109-0.flt
	//Flt/mi17/MI_17_lod.flt
	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile( "255-109-0.flt" );

	//класс для извлечения данных геометрии
	osg::ref_ptr< TransGeomNode2VertArray > converter = new TransGeomNode2VertArray;

	//реорганизовать геометрию к треугольникам
	converter->apply( *model.get() );

	//создание из 1 модели нескольких копий
	CreateBigModel( converter->GetVertex() 
		, converter->GetNormals()
		, converter->GetTexCoord0() );

	//m_rootNode->addChild( model.get() );
}

void CompoundModel::CreateBigModel( const osg::Vec3Array *_v 
										 , const osg::Vec3Array *_n
										 , const osg::Vec2Array *_tc0 )
{
	//создание из 1 модели нескольких копий

	osg::ref_ptr< osg::Node > node = new osg::Node;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec4Array> v = new osg::Vec4Array;
	geom->setVertexArray( v.get() );

//////////////////////////////////////////////////////////////////////////
	for ( int j = 0 ; j < NUM_COPY ; ++j )
		for ( int i = 0 ; i < _v->size() ; ++i )
		{
			v->push_back( osg::Vec4( _v->at( i ).x(), _v->at( i ).y(), _v->at( i ).z() 
				, (float)j / (float)NUM_COPY + 1.0 / 256.0 ) );
		}
//////////////////////////////////////////////////////////////////////////

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalBinding( osg::Geometry::BIND_PER_VERTEX );
	geom->setNormalArray( n.get() );

//////////////////////////////////////////////////////////////////////////
	for ( int j = 0 ; j < NUM_COPY ; ++j )
		for ( int i = 0 ; i < _n->size() ; ++i )
			n->push_back( _n->at( i ) );
//////////////////////////////////////////////////////////////////////////

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );

//////////////////////////////////////////////////////////////////////////
	for ( int j = 0 ; j < NUM_COPY ; ++j )
		for ( int i = 0 ; i < _tc0->size() ; ++i )
			tc->push_back( _tc0->at( i ) );
//////////////////////////////////////////////////////////////////////////

	geom->addPrimitiveSet( new osg::DrawArrays( osg::PrimitiveSet::TRIANGLES, 0, v->size() ) );

	//добавить город
	AddCity( geom.get() );
}

void CompoundModel::AddTexture()
{
	//добавить текстуру
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image>image0 = osgDB::readImageFile( "VillageTmplHouses.png" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );
}

void CompoundModel::AddShader()
{
	//добавить шейдер

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "compound_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/compound.vert" );
	LoadShaderSource( FragObj , "glsl/compound.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );
}

void CompoundModel::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
{
	// load source from a file.
	std::string fqFileName = osgDB::findDataFile(fileName);
	if( fqFileName.length() != 0 )
	{
		shader->loadShaderSourceFromFile( fqFileName.c_str() );
	}
	else
	{
		osg::notify(osg::WARN) << "File \"" << fileName << "\" not found." << std::endl;
	}
}

void CompoundModel::CreateDynamicImage()
{
	//создать картинку, содержащую смещения геометрии
	
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	//картинка с координатами
	osg::ref_ptr<osg::Image> image = new osg::Image;

	//размер картинки 128 на 128 
	image->allocateImage( 128, 128, 1, GL_RGBA, GL_FLOAT ); 

	image->setInternalTextureFormat( GL_RGBA_FLOAT32_ATI );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST);
	tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST);
	tex->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP); 
	tex->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP);

	tex->setImage( image.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 1, tex.get() , osg::StateAttribute::ON );

	//передать динамически меняемую картинку
	m_rpCompoundUpdateCallback->SetDynamicImage( image.get() );
}

void CompoundModel::AddCity( osg::ref_ptr< osg::Geometry > _geom )
{
	//добавить город

	for ( int i = 0 ; i < NUM_COPY ; ++i )
	{
		// Add the Geometry (Drawable) to a Geode and
		// return the Geode.
		osg::ref_ptr< osg::Geode > geode = new osg::Geode;

		osg::StateSet* state = geode->getOrCreateStateSet();

		//добавление uniform'ов для работы с текстурными модулями
		state->addUniform( new osg::Uniform( "offset_y" , (float)i / (float)NUM_COPY + 1.0f / 256.0f ) );

		geode->addDrawable( _geom.get() );

		m_rootNode->addChild( geode.get() );
	}
}