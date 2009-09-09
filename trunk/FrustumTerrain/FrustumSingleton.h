#ifndef _FRUSTUM_SINGLETON_H_
#define _FRUSTUM_SINGLETON_H_

#include "Singleton.h"

#include <osg/Matrix>
#include <osg/Array>

class FrustumSingleton : public Singleton< FrustumSingleton >
{
public:
	FrustumSingleton();
	~FrustumSingleton();

	//�������� ���������� ������� ��������
	void UpdateProjection( osg::Matrix proj );

	//�������� ��������� ��������� ������
	void UpdateFrustum( osg::Matrix inv_mv );

	//����������� ��������� BOX'a
	bool BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx );

	//������ ��������� �����������
	void SetViewPos( osg::Vec3 pos ){ m_Pos = pos; };

	//������� ��������� �����������
	osg::Vec3 GetViewPos() const { return m_Pos; };

private:

	//��������� ��������� ���������
	void CalcClipPlanes();

	//��������� ��������� ��������� �� ���� ������
	osg::Vec4 MakePlane( osg::Vec3 P1 , osg::Vec3 P2 , osg::Vec3 P3 );

	//�������� ������ �����
	osg::ref_ptr< osg::Vec3Array > vOrig;

	//������� ������ �����
	osg::ref_ptr< osg::Vec3Array > vTrans;

	//����� ����������, �������������� ������� �����
	osg::Vec4 plane[6];

	//��������� �����������
	osg::Vec3 m_Pos;
};

#endif	//_FRUSTUM_SINGLETON_H_