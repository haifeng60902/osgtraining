#ifndef _DATA_VIS_PATCH_H_
#define _DATA_VIS_PATCH_H_

#include <osg/Geode>
#include <osg/Uniform>

#define DIST_SCALE 3.9f
#define GEOM_DIV 1

struct dataVisPatch
{
	dataVisPatch() : m_sOffset( "posOffset" )
		, m_sColorP( "colorP" )
		, m_sColorS( "colorS" )
		, m_sDist( "dist" )
	{};

	//��������� �����
	osg::ref_ptr< osg::Geode > m_Geode;

	//uniform ��� ������������� �������� ��������� �����
	osg::ref_ptr< osg::Uniform > m_unfOffset;

	//uniform ��� ������� ��������� �����
	osg::ref_ptr< osg::Uniform > m_unfColorP;

	//uniform ��� ������� ���������������� �����
	osg::ref_ptr< osg::Uniform > m_unfColorS;

	//uniform ��� ������� ����������
	osg::ref_ptr< osg::Uniform > m_unfDist;

	//��� ���������� ��������
	std::string m_sOffset;

	//��� ���������� ��������� �����
	std::string m_sColorP;

	//��� ���������� ���������������� �����
	std::string m_sColorS;

	//��� ���������� ����������
	std::string m_sDist;
};

#endif	//_DATA_VIS_PATCH_H_