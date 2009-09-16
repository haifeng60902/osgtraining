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

	//вернуть ствол с LOD'ами
	osg::ref_ptr< osg::LOD > getBranchLOD(){ return m_BranchLOD.get(); };

private:
	//инициировать корневой узел данными
	osg::ref_ptr< osg::Geode > InitBranchGeode( int iLOD );

	//создать LOD ствола
	void CreateBranchLOD();

	//добавить текстуру
	void AddTexture();

	//настроить альфа канал
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//расчет новых значений видимости LOD'ов
	void CalcNewLODDist( float i , float fSize
		, float fNear , float fFar , float *fLODNear , float *fLODFar );

	//узел с геометрией ствола
	osg::ref_ptr< osg::LOD > m_BranchLOD;

	//начало и конец работы LOD'ов
	float m_fNear;
	float m_fFar;
};

#endif	//_BRANCH_XML_H_