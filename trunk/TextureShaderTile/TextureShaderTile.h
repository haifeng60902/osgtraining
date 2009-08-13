#ifndef _TEXTURE_SHADER_TILE_H_
#define _TEXTURE_SHADER_TILE_H_

#include <osg/Referenced>
#include <osg/Geode>
#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Image>

class TextureShaderTile : public osg::Referenced
{
public:
	TextureShaderTile();
	~TextureShaderTile();

	//������� ���� ���������� ���
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

	//������� uniform ������������ ��������
	osg::ref_ptr< osg::Uniform > GetUniformOffsetX(){ return m_OffsetX.get(); };
	osg::ref_ptr< osg::Uniform > GetUniformOffsetY(){ return m_OffsetY.get(); };

	osg::ref_ptr< osg::Uniform > GetUniformScaleX(){ return m_ScaleX.get(); };
	osg::ref_ptr< osg::Uniform > GetUniformScaleY(){ return m_ScaleY.get(); };

	osg::ref_ptr< osg::Uniform > GetUniformOffsetScaleX(){ return m_OffsetScaleX.get(); };
	osg::ref_ptr< osg::Uniform > GetUniformOffsetScaleY(){ return m_OffsetScaleY.get(); };

private:
	//���������������� ���������
	void InitGeom();

	//�������� ������
	void AddShader();

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� �������� ��������
	void AddTextureIndex();

	//�������� �������� � �������
	void AddTextureTile();

	//�������� �������� ����������
	void AddTextureRepeat();

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	osg::ref_ptr< osg::Uniform > m_OffsetX;
	osg::ref_ptr< osg::Uniform > m_OffsetY;

	osg::ref_ptr< osg::Uniform > m_ScaleX;
	osg::ref_ptr< osg::Uniform > m_ScaleY;

	osg::ref_ptr< osg::Uniform > m_OffsetScaleX;
	osg::ref_ptr< osg::Uniform > m_OffsetScaleY;
};

#endif	//_TEXTURE_SHADER_TILE_H_