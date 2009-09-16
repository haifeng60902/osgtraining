#include "TerrainSimplePatchNode.h"

#include "DynamicGroupUpdateCallback.h"

#include <osgDB/ReadFile>
#include <osg/Texture2D>

TerrainSimplePatchNode::TerrainSimplePatchNode()
{
	m_rootNode = new osg::Group;

	//���������������� �������� ���� �����
	InitTerrainNode();

	//����������� �������� ����
	m_rootNode->setDataVariance( osg::Object::DYNAMIC );

	//��������� ��������� ��������� LOD �����
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	//������������� ��������� ���������
	state->setMode( GL_LIGHTING, osg::StateAttribute::OFF |
			osg::StateAttribute::PROTECTED );
}

TerrainSimplePatchNode::~TerrainSimplePatchNode()
{

}

void TerrainSimplePatchNode::InitTerrainNode()
{
	//���������������� �������� ���� �����

	//�������� �������� � �������
	AddTextureTile();

	//����������� �������� ����
	m_rootNode->setUpdateCallback( new DynamicGroupUpdateCallback );
}

void TerrainSimplePatchNode::AddTextureTile()
{
	//�������� �������� � �������
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();

	// Load the texture image
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile( "big.bmp" );

	// Attach the image in a Texture2D object
	osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
	tex->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR );
	tex->setWrap(osg::Texture::WRAP_S,osg::Texture::REPEAT); 
	tex->setWrap(osg::Texture::WRAP_T,osg::Texture::REPEAT); 

	tex->setImage( image.get() );

	//���������� ������ �� image
	//tex->setUnRefImageDataAfterApply( true );

	// Attach the 2D texture attribute and enable GL_TEXTURE_2D,
	// both on texture unit 1.
	state->setTextureAttributeAndModes( 0 , tex.get() );
}