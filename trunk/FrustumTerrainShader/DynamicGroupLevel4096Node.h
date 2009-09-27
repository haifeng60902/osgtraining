#ifndef _DYNAMIC_GROUP_LEVEL_4096_NODE_H_
#define _DYNAMIC_GROUP_LEVEL_4096_NODE_H_

#include <osg/Group>
#include <osg/Geode>
#include <osg/Referenced>
#include <osg/ref_ptr>

#include <vector>

class DynamicGroupLevel4096Node : public osg::Referenced
{
public:
	struct Data
	{
		//��������� �����
		osg::ref_ptr< osg::Geode > m_Geode;

		//uniform ��� ������������� ����������
		osg::ref_ptr< osg::Uniform > m_Uniform;
	};

	DynamicGroupLevel4096Node();

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
	void FillIndexVector( std::vector< unsigned int > &m_vIndex , int sizeC );

	//������� ������ ������
	osg::ref_ptr<osg::Vec3Array> CreateVertexArray( int x , int y , int sizeC , int scaleC );

	//�������, ����� ��� ���� �����
	std::vector< unsigned int > m_vIndex;

	//�������� ����
	osg::ref_ptr< osg::Group > m_rootNode;

	//������ ���������
	std::vector< Data > m_vData;

	//������� ����������� �����
	int m_iCount;
};

#endif	//_DYNAMIC_GROUP_LEVEL_4096_NODE_H_