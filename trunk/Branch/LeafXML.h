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

	//вернуть листву с LOD'ами
	osg::ref_ptr< osg::LOD > getLeafLOD(){ return m_LeafLOD.get(); };

private:

	//создать LOD'ы листвы
	void CreateLeafLOD();

	//вернуть геометрию заданного LOD'a
	osg::ref_ptr< osg::Geode > InitLeafGeode( int iLOD );

	//добавить текстуры
	void AddTextures();

	//настроить альфа канал
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//расчет новых значений видимости LOD'ов
	void CalcNewLODDist( float i , float fSize
		, float fNear , float fFar , float *fLODNear , float *fLODFar );

	//узел с геометрией листвы
	osg::ref_ptr< osg::LOD > m_LeafLOD;

	//начало и конец работы LOD'ов
	float m_fNear;
	float m_fFar;
};

#endif	//_LEAF_XML_H_