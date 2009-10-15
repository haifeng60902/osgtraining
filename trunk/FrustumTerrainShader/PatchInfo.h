#ifndef _PATCH_INFO_H_
#define _PATCH_INFO_H_

#include "Singleton.h"
#include "binData/binPatch.h"

#include <osg/Image>

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
private:

	//����� ������������� 16 �� 16
	binPatch m_binPatch[16][16];

	//����������� ���������� �������
	osg::ref_ptr<osg::Image> m_ImageIndex;
};

#endif	//_PATCH_INFO_H_