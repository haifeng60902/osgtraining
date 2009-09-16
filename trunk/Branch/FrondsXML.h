#ifndef _FRONDS_XML_H_
#define _FRONDS_XML_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Geode>

class FrondsXML : public osg::Referenced
{
public:
	FrondsXML( float fNear , float fFar );
	~FrondsXML();

	//������� LOD'� �����
	osg::ref_ptr< osg::LOD > getFrondsLOD(){ return m_FrondsLOD.get(); };

private:

	//������� LOD'� �����
	void CreateFrondsLOD();

	//������������ �������� ���� �������
	osg::ref_ptr< osg::Geode > InitFrondsGeode( int iLOD );

	//������ ����� �������� ��������� LOD'��
	void CalcNewLODDist( float i , float fSize
		, float fNear , float fFar , float *fLODNear , float *fLODFar );

	//�������� ��������
	void AddTexture();

	//��������� ����� �����
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//���� � ���������� �����
	osg::ref_ptr< osg::LOD > m_FrondsLOD;

	//������ � ����� ������ LOD'��
	float m_fNear;
	float m_fFar;
};

#endif	//_FRONDS_XML_H_