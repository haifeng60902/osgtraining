#include "Lighting.h"

#include <osgDB/ReadFile>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/Point>
#include <osg/MatrixTransform>
#include <osg/LightSource>
#include <osg/PolygonMode>
#include <osg/Material>
#include <osg/LightModel>

Lighting::Lighting()
{
	buildScene();
}

Lighting::~Lighting()
{

}

void Lighting::buildScene()
{
	// the root of our scenegraph.
	m_rootGroup = new osg::Group;

	// Load the cow model.
	m_rootGroup->addChild( LoadModel().get() );

	m_rootGroup->addChild( CreatePlane().get() );

	m_rootGroup->addChild( CreateLight().get() );
}

osg::ref_ptr< osg::Node > Lighting::LoadModel()
{
	//загрузить модель
	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile( "Flt/mi17/MI_17_lod.flt" );

	osg::ref_ptr<osg::Material> mat = new osg::Material;

	mat->setAmbient( osg::Material::FRONT,
		osg::Vec4( 0.0f, 1.0f, 0.0f, 1.f ) );
	mat->setDiffuse( osg::Material::FRONT,
		osg::Vec4( 0.f, 1.f, 0.f, 1.f ) );
	mat->setSpecular( osg::Material::FRONT,
		osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
	mat->setShininess( osg::Material::FRONT, 128.f );

	//добавить текстуру
	osg::StateSet* state = model->getOrCreateStateSet();

	state->setAttribute( mat.get() );

	return model.get();
}

osg::ref_ptr< osg::Node > Lighting::CreatePlane()
{
	//создать плоскость
	osg::ref_ptr<osg::Group> plane = new osg::Group;

	// Create an object to store geometry in.
	osg::ref_ptr< osg::Geometry > geom = new osg::Geometry;

	// Create an array of four vertices.
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );

	// Create a Vec2Array of texture coordinates for texture unit 0
	// and attach it to the geom.
	osg::ref_ptr<osg::Vec2Array> tc = new osg::Vec2Array;
	geom->setTexCoordArray( 0, tc.get() );

//////////////////////////////////////////////////////////////////////////
	int sizeC=513;
	//Заполнение массива points
	for (int i = 0 ; i < sizeC ; ++i )
		for (int j = 0 ; j < sizeC ; ++j )
	{
		v->push_back( osg::Vec3( j - sizeC / 2.0, i - sizeC / 2.0, -2.4f ) );
		tc->push_back( osg::Vec2( j / ( sizeC - 1.0 ) , i / ( sizeC - 1.0 )  ) );
	}

	m_vIndex.push_back( 0 );
	m_vIndex.push_back( sizeC );
	int count = sizeC - 1;
	int ind = 0;
	while( count > 0 )
	{
		for( int i = 0 ; i < count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + 1 );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + 1 );
		}
		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );
		count--;

		for( int i = 0 ; i< count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + sizeC );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] + sizeC );
		}

		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );

		for( int i = 0 ; i < count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - 1 );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - 1 );
		}

		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );
		count--;

		for( int i=0 ; i < count ; i++ )
		{
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - sizeC );
			ind = m_vIndex.size() - 2;
			m_vIndex.push_back( m_vIndex[ ind ] - sizeC );
		}
		ind = m_vIndex.size() - 3;
		m_vIndex.push_back( m_vIndex[ ind ] );
	}


//////////////////////////////////////////////////////////////////////////

	// Create an array for the single normal.
	osg::ref_ptr< osg::Vec3Array > n = new osg::Vec3Array;
	geom->setNormalArray( n.get() );
	geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
	n->push_back( osg::Vec3( 0.f, 0.f, 1.f ) );

	geom->addPrimitiveSet( new osg::DrawElementsUInt(
		osg::PrimitiveSet::TRIANGLE_STRIP, m_vIndex.size(), &m_vIndex[ 0 ] ) );

	// Add the Geometry (Drawable) to a Geode and
	// return the Geode.
	osg::ref_ptr< osg::Geode > geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	plane->addChild( geode.get() );

	//динамически меняемый узел
	plane->setDataVariance( osg::Object::STATIC );

//////////////////////////////////////////////////////////////////////////
	//добавить текстуру
	osg::StateSet* state = plane->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image>image0 = osgDB::readImageFile( "Images/level0017-row000104-col000096.dds" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex0 = new osg::Texture2D;
	tex0->setImage( image0.get() );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 0, tex0.get() , osg::StateAttribute::ON );

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode( osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE );
	//state->setAttributeAndModes( polymode, osg::StateAttribute::ON );

//////////////////////////////////////////////////////////////////////////
	osg::ref_ptr<osg::Material> mat = new osg::Material;

	mat->setAmbient( osg::Material::FRONT,
		osg::Vec4( 0.9f, 0.9f, 0.9f, 1.f ) );
	mat->setDiffuse( osg::Material::FRONT,
		osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
	mat->setSpecular( osg::Material::FRONT,
		osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );
	mat->setShininess( osg::Material::FRONT, 128.f );
	//mat->setEmission( osg::Material::FRONT , osg::Vec4( 1, 1, 1, 1) );
	state->setAttribute( mat.get() );

	osg::LightModel* lightModel = new osg::LightModel;
	lightModel->setAmbientIntensity(osg::Vec4( 0.0f , 0.0f , 0.0f , 1.0f ) );
	lightModel->setLocalViewer( true );
	lightModel->setColorControl( osg::LightModel::SEPARATE_SPECULAR_COLOR );

	//установить атрибут глобального фонового освещения
	state->setAttribute( lightModel , osg::StateAttribute::ON );

	return plane.get();
}

osg::ref_ptr< osg::Geode > Lighting::createLightPoint()
{
	//создать точку представляющую источник света
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	// Don't throw away single-vertex primitives.
	osg::BoundingBox bbox( -.1f, -.1f, -.1f, .1f, .1f, .1f );
	geom->setInitialBound( bbox );

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray( v.get() );
	v->push_back( osg::Vec3( 0.f, 0.f, 5.f ) );

	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray( c.get() );
	geom->setColorBinding( osg::Geometry::BIND_OVERALL );
	c->push_back( osg::Vec4( 1.f, 1.f, 1.f, 1.f ) );

	geom->addPrimitiveSet( new osg::DrawArrays( GL_POINTS, 0, 1 ) );

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable( geom.get() );

	osg::StateSet* state = geode->getOrCreateStateSet();
	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
		osg::StateAttribute::PROTECTED );

	osg::ref_ptr<osg::Point> pt = new osg::Point;
	pt->setSize( 10.f );
	state->setAttribute( pt.get() );

	return geode.get();
}

osg::ref_ptr< osg::Transform > Lighting::CreateLight()
{
	//создать источник света

	// Represent the two light sources with a shared point.
		// Each light's position is 0,0,0 in object coordinates. The
		//   two parent MatrixTransforms translate the lights, and the
		//   shared point, to their actual positions.
	osg::ref_ptr<osg::Geode> lightPoint = createLightPoint();

	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	osg::Matrix m;
	m.makeTranslate( osg::Vec3( 0.f, 0.f, 5.f ) );
	mt->setMatrix( m );

	// Create a mostly red light
	osg::ref_ptr<osg::Light> light = new osg::Light;
	light->setLightNum( 0 );
	light->setPosition( osg::Vec4( 0.f, 0.f, 0.f, 1.f));
	light->setAmbient( osg::Vec4( 0.0f, 0.0f, 0.0f, 1.f));
	light->setDiffuse( osg::Vec4( 1.f, 1.0f, 1.0f, 1.f));
	light->setSpecular( osg::Vec4( 1.f, .1f, .1f, 1.f));

	light->setConstantAttenuation( 0.0001 );
	light->setLinearAttenuation( 0.0001 );
	light->setQuadraticAttenuation( 0.0001 );

	osg::ref_ptr<osg::LightSource> ls = new osg::LightSource;
	mt->addChild( ls.get() );
	ls->setLight( light.get() );
	ls->addChild( lightPoint.get() );

	return mt.get();
}