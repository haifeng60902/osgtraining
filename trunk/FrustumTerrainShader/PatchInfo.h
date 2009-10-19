#ifndef _PATCH_INFO_H_
#define _PATCH_INFO_H_

#include "Singleton.h"
#include "binData/binPatch.h"
#include "binData/enumTypes.h"

#include <osg/Image>

#include <map>

class PatchInfo : public Singleton< PatchInfo >
{
public:
	PatchInfo();
	~PatchInfo();

	//���������������� ������ � ���������� ������
	void InitPatchData();

	//������������� ������� ���������� ���� ����� � ���� ��������
	void Convert( double dX , double dY , unsigned char *ucR , unsigned char *ucG );

	//������� ������ �� ������ � ���������� ������
	binPatch &GetBinPatch( unsigned char ucR , unsigned char ucG ){ return m_binPatch[ ucG ][ ucR ]; };

	//������� ���� �� ���� �� ��� ����
	osg::ref_ptr< osg::Node > GetModel( eHouse _house );

private:
	typedef std::map< eHouse , osg::ref_ptr< osg::Node > > tMapModelCache;

	//����� ������������� 16 �� 16
	binPatch m_binPatch[16][16];

	//����������� ���������� �������
	osg::ref_ptr<osg::Image> m_ImageIndex;

	//������������ ������
	tMapModelCache m_ModelCache;
};

#endif	//_PATCH_INFO_H_