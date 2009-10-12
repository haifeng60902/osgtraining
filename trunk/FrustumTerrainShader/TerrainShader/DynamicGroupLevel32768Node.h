#ifndef _DYNAMIC_GROUP_LEVEL_32768_NODE_H_
#define _DYNAMIC_GROUP_LEVEL_32768_NODE_H_

#include "dataVisPatch.h"

#include <osg/Group>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <vector>

class DynamicGroupLevel32768Node : public osg::Referenced
{
public:
	struct Data
	{
		//��������� �����
		osg::ref_ptr< osg::Geode > m_Geode;

		//uniform ��� ������������� ����������
		osg::ref_ptr< osg::Uniform > m_Uniform;

		//uniform ��� ������������� ������� �����
		osg::ref_ptr< osg::Uniform > m_UniformColor;
	};

	DynamicGroupLevel32768Node();

	//������� ���� ���������� �����
	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

	//������� ���� �������� ��������� ����
	void ResetRootNode();

	//�������� ���� ��������� �� ������� � �������� ����
	void AddPatch( float x , float y );

	//������� ���������� ����� ��� ���������
	void PrintSize();

private:

	//���������������� ��������� ������ ������ �����������
	void InitGeodes();

	//�������� ��������� � i'�� ����
	void AddGeometry( int i );

	//��������� ��������� ����������� � �������
	void SetupShaderParam( int i );

	//��������� ������ ���������
	void FillIndexVector( std::vector< unsigned short > &m_vIndex , int sizeC );

	//������� ������ ������
	osg::ref_ptr<osg::Vec4Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	//������ ���������
	std::vector< dataVisPatch > m_vData;

	//������� ����������� �����
	int m_iCount;
};

#endif	//_DYNAMIC_GROUP_LEVEL_32768_NODE_H_