#ifndef _BILLBOARDS_H_
#define _BILLBOARDS_H_

#include "LightSource.h"

#include <osg/Referenced>
#include <osg/Group>
#include <osg/ref_ptr>
#include <osg/Program>
#include <osg/Texture2D>

class Billboards : public osg::Referenced
{
public:
	Billboards();
	~Billboards();

	//������� ��������� �� �������� ������
	osg::ref_ptr< osg::Group > getRootGroup() { return m_rootGroup.get(); }

private:
	//��������� ��������
	void LoadTexture();

	//������������ ����� � ��������
	void buildSceneShader();

	//������������ �����
	void buildScene();

	//�������� ���������
	void AddPlane();

	//��������� ���������
	void SetupStateSet( osg::StateSet* ss );

	//�������� ������ � �����
	void AddShader( osg::StateSet* ss );

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//�������� ��������� �����
	float GetRand( float fScale );

	//�������� ������, ���������� ���������
	osg::ref_ptr< osg::Group > m_rootGroup;

	//����� ��������
	osg::ref_ptr<osg::Texture2D> m_Tex0;

	//�������� �����
	LightSource m_LightSource;
};

#endif	//_BILLBOARDS_H_