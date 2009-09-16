#ifndef _BRANCH_XML_H_
#define _BRANCH_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>
#include <osg/lod>

class BranchXML : public osg::Referenced
{
public:
	BranchXML( float fNear , float fFar );
	~BranchXML();

	//osg::ref_ptr< osg::Geode > getBranchGeode() { return m_branchGeode.get(); }

	//������� ����� � LOD'���
	osg::ref_ptr< osg::LOD > getBranchLOD(){ return m_BranchLOD.get(); };

private:
	//������������ �������� ���� �������
	osg::ref_ptr< osg::Geode > InitBranchGeode( int iLOD );

	//������� LOD ������
	void CreateBranchLOD();

	//�������� ��������
	void AddTexture();

	//��������� ����� �����
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//������ ����� �������� ��������� LOD'��
	void CalcNewLODDist( float i , float fSize
		, float fNear , float fFar , float *fLODNear , float *fLODFar );

	//���� � ���������� ������
	osg::ref_ptr< osg::LOD > m_BranchLOD;

	//������ � ����� ������ LOD'��
	float m_fNear;
	float m_fFar;
};

#endif	//_BRANCH_XML_H_