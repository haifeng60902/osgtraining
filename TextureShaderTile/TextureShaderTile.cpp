#include "TextureShaderTile.h"

#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/Image>
#include <osgDB/FileUtils>
#include <osg/Texture2D>
#include <osg/AlphaFunc>
#include <osg/CullFace>

TextureShaderTile::TextureShaderTile()
{
	m_rootNode = new osg::Group;

	//инициализировать геометрию
	InitGeom();

	//добавить текстуру индексов
	AddTextureIndex();

	//добавить текстуру с тайлами
	AddTextureTile();

	//добавить текстуру повторений
	AddTextureRepeat();

	//добавить шейдер
	AddShader();
}

TextureShaderTile::~TextureShaderTile()
{

}

void TextureShaderTile::InitGeom()
{
	//инициализировать геометрию

	//Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	v->push_back( osg::Vec3( -1.0 , 0 , -1.0 ) );
	v->push_back( osg::Vec3( 1.0 , 0 , -1.0 ) );
	v->push_back( osg::Vec3( 1.0 , 0 , 1.0 ) );
	v->push_back( osg::Vec3( -1.0 , 0 , 1.0 ) );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	tc->push_back( osg::Vec2( 0.0 , 0.0 ) );
	tc->push_back( osg::Vec2( 1 , 0.0 ) );
	tc->push_back( osg::Vec2( 1 , 1 ) );
	tc->push_back( osg::Vec2( 0 , 1 ) );

	geom->setVertexArray( v.get() );
	geom->setTexCoordArray( 0, tc.get() );

	geom->addPrimitiveSet( new osg::DrawArrays(
		osg::PrimitiveSet::QUADS , 0 , 4 ) );

	//корневой узел геометрии листвы
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;

	geode->addDrawable( geom.get() );

	m_rootNode->addChild( geode.get() );
}

void TextureShaderTile::AddTextureIndex()
{
	//добавить текстуру индексов
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile( "index.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::NEAREST );
	tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::NEAREST );
	tex->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP); 
	tex->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP); 

	tex->setImage( image.get() );

	//освободить память от image
	tex->setUnRefImageDataAfterApply( true );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0 , tex.get() );
}

void TextureShaderTile::AddTextureTile()
{
	//добавить текстуру с тайлами
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile( "big.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setWrap(osg::Texture::WRAP_S,osg::Texture::CLAMP); 
	tex->setWrap(osg::Texture::WRAP_T,osg::Texture::CLAMP); 

	tex->setImage( image.get() );

	//освободить память от image
	tex->setUnRefImageDataAfterApply( true );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 1 , tex.get() );
}

void TextureShaderTile::AddTextureRepeat()
{
	//добавить текстуру повторений
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	osg::ref_ptr< osg::Image > imageR = new osg::Image;
	imageR->allocateImage( 256, 256, 1, GL_RGB, GL_UNSIGNED_BYTE); 
	{
		unsigned char *dataR = imageR->data();

		//получить размер текстуры
		int t = imageR->t();
		int s = imageR->s();
		int byte = imageR->getPixelSizeInBits() / 8;

		for ( int y = 0 ; y < t ; ++y )
			for ( int x = 0 ; x < s ; ++x )
			{
				//записать преобразованный цвет
				/*
				if ( x == 1)
					dataR[ y * s * byte + x * byte ] = 0;
				else
					if ( x == 255 )
						dataR[ y * s * byte + x * byte ] = 254;
				else
					dataR[ y * s * byte + x * byte ] = x;

				if ( y == 1)
					dataR[ y * s * byte + x * byte  + 1] = 0;
				else
					if ( y == 255 )
						dataR[ y * s * byte + x * byte + 1] = 254;
					else
						dataR[ y * s * byte + x * byte + 1] = y;

				*/
				dataR[ y * s * byte + x * byte ] = x;
				dataR[ y * s * byte + x * byte + 1 ] = y;
				dataR[ y * s * byte + x * byte + 2 ] = 0;
			}
	}

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	tex->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT); 
	tex->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT); 

	tex->setImage( imageR.get() );

	//освободить память от image
	tex->setUnRefImageDataAfterApply( true );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 2 , tex.get() );

}

void TextureShaderTile::AddShader()
{
	//добавить шейдер в сцену

	//формирование сцены с шейдером
	osg::StateSet* ss = m_rootNode->getOrCreateStateSet();

	//создать экземпляр программы
	osg::Program* program = new osg::Program;
	program->setName( "quad_shader" );

	osg::Shader *VertObj = new osg::Shader( osg::Shader::VERTEX );
	osg::Shader *FragObj = new osg::Shader( osg::Shader::FRAGMENT );
	program->addShader( VertObj );
	program->addShader( FragObj );

	LoadShaderSource( VertObj , "glsl/quad.vert" );
	LoadShaderSource( FragObj , "glsl/quad.frag" );

	ss->setAttributeAndModes( program, osg::StateAttribute::ON );

	//добавление uniform'ов для работы с текстурными модулями
	ss->addUniform( new osg::Uniform( "u_texture0" , 0 ) );
	ss->addUniform( new osg::Uniform( "u_texture1" , 1 ) );
	ss->addUniform( new osg::Uniform( "u_texture2" , 2 ) );

	//управляемое смещение
	m_OffsetX = new osg::Uniform( "offsetX" , 0.0f );
	ss->addUniform( m_OffsetX.get() );
	m_OffsetY = new osg::Uniform( "offsetY" , 0.0f );
	ss->addUniform( m_OffsetY.get() );

	m_ScaleX = new osg::Uniform( "scaleX" , 1.0f );
	ss->addUniform( m_ScaleX.get() );
	m_ScaleY = new osg::Uniform( "scaleY" , 1.0f );
	ss->addUniform( m_ScaleY.get() );

	m_OffsetScaleX = new osg::Uniform( "offsetScaleX" , 0.0f );
	ss->addUniform( m_OffsetScaleX.get() );
	m_OffsetScaleY = new osg::Uniform( "offsetScaleY" , 0.0f );
	ss->addUniform( m_OffsetScaleY.get() );
}

void TextureShaderTile::LoadShaderSource( osg::Shader* shader, const std::string& fileName )
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
