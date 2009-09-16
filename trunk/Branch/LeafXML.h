#ifndef _LEAF_XML_H_
#define _LEAF_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>

class LeafXML : public osg::Referenced
{
public:
	LeafXML( float fNear , float fFar );
	~LeafXML();

	//������� ������ � LOD'���
	osg::ref_ptr< osg::LOD > getLeafLOD(){ return m_LeafLOD.get(); };

private:

	//������� LOD'� ������
	void CreateLeafLOD();

	//������� ��������� ��������� LOD'a
	osg::ref_ptr< osg::Geode > InitLeafGeode( int iLOD );

	//�������� ��������
	void AddTextures();

	//��������� ����� �����
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//������ ����� �������� ��������� LOD'��
	void CalcNewLODDist( float i , float fSize
		, float fNear , float fFar , float *fLODNear , float *fLODFar );

	//���� � ���������� ������
	osg::ref_ptr< osg::LOD > m_LeafLOD;

	//������ � ����� ������ LOD'��
	float m_fNear;
	float m_fFar;
};

#endif	//_LEAF_XML_H_