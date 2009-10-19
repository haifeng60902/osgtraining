#include "TerrainNode.h"

#include <osg/BoundingBox>
#include <osg/PolygonMode>
#include <osg/Image>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

TerrainNode::TerrainNode()
{
	//создать главный узел
	m_rootNode = new osg::Group;

	//инициализировать корневой узел земли
	InitTerrainNode();

	//инициализировать корневой узел строений
	InitBuildingNode();

	//добавить текстуру с картой высот
	AddTextureHeightmap();

	//добавить режим отображения 
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	osg::PolygonMode* polymode = new osg::PolygonMode;
	polymode->setMode( osg::PolygonMode::FRONT_AND_BACK , osg::PolygonMode::LINE );
	//state->setAttributeAndModes( polymode, osg::StateAttribute::ON );

	//динамически меняемый узел
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );
}

TerrainNode::~TerrainNode()
{

}

void TerrainNode::InitTerrainNode()
{
	//инициализировать корневой узел земли

	// определение ограничивающего объема, размер земли 256км(в 1 км - 1024 метра), максимальная высота 500м
	osg::BoundingBox bbox( 0, 0, 0, 512 * 512 , 512 * 512 , 64 );
	m_rootNode->setInitialBound( bbox );

	//класс отвечающий за формирование и вывод земной поверхности
	m_TerrainShaderPatchNode = new TerrainShaderPatchNode;

	//добавить узел ратчей
	m_rootNode->addChild( m_TerrainShaderPatchNode->getRootNode().get() );
}

void TerrainNode::InitBuildingNode()
{
	//инициализировать корневой узел строений

	//класс отвечающий за формирование и вывод земной поверхности
	m_BuildingShaderPatchNode = new BuildingShaderPatchNode;

	//добавить узел со строениями
	m_rootNode->addChild( m_BuildingShaderPatchNode->getRootNode().get() );
}

void TerrainNode::AddTextureHeightmap()
{
	//добавить текстуру с картой высот
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image0 =
		osgDB::readImageFile( "terHightmap.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex2 = new osg::Texture2D;
	tex2->setImage( image0.get() );

	tex2->setFilter( osg::Texture::MIN_FILTER,osg::Texture::LINEAR );
	tex2->setFilter( osg::Texture::MAG_FILTER,osg::Texture::LINEAR );
	tex2->setWrap( osg::Texture::WRAP_S , osg::Texture::REPEAT ); 
	tex2->setWrap( osg::Texture::WRAP_T , osg::Texture::REPEAT ); 

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 0.
	state->setTextureAttributeAndModes( 2, tex2.get() , osg::StateAttribute::ON );

	tex2->setUnRefImageDataAfterApply( true );
}