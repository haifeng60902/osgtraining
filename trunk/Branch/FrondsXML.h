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

	//вернуть LOD'ы веток
	osg::ref_ptr< osg::LOD > getFrondsLOD(){ return m_FrondsLOD.get(); };

private:

	//создать LOD'ы веток
	void CreateFrondsLOD();

	//инициировать корневой узел данными
	osg::ref_ptr< osg::Geode > InitFrondsGeode( int iLOD );

	//расчет новых значений видимости LOD'ов
	void CalcNewLODDist( float i , float fSize
		, float fNear , float fFar , float *fLODNear , float *fLODFar );

	//добавить текстуру
	void AddTexture();

	//настроить альфа канал
	void SetupAlfaFunc( osg::ref_ptr< osg::Geode > geode , int iLOD );

	//узел с геометрией веток
	osg::ref_ptr< osg::LOD > m_FrondsLOD;

	//начало и конец работы LOD'ов
	float m_fNear;
	float m_fFar;
};

#endif	//_FRONDS_XML_H_