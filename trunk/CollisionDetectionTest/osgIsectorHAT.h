#ifndef _OSG_ISECTOR_HAT_H_
#define _OSG_ISECTOR_HAT_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Switch>


class osgIsectorHAT : public osg::Referenced
{
public:
	osgIsectorHAT();

	//������ �������� �����������
	void setTarget( osg::ref_ptr< osg::Node > _node ){ m_SceneRoot = _node; };

	//��������� isector'a
	void setEnable( bool _bEnable ){ m_bEnable = _bEnable; };

	//������� ��������� �����������
	void setPositionReference( osg::ref_ptr< osg::MatrixTransform > _mt );

	//�������� ����� ����������� ����� isector'a
	void setRenderEnable( bool _bEnable );

	//������ isector'a
	void setSegmentZExtent( float _dMinZ , float _dMaxZ );

	//������ ������ �����������
	float GetHAT();

private:
	
	//�������� ����� ��� ���������� �����
	void InitLine();

	//��������� isector'a
	bool m_bEnable;

	//����� ����������� isector'a
	bool m_bRender;

	//osg::Switch ��� ���������/���������� ����������� isector'a
	osg::ref_ptr< osg::Switch > m_Switch;

	//������� �����
	osg::ref_ptr<osg::Vec3Array> m_v3V;

	//���� �����
	osg::ref_ptr<osg::Vec4Array> m_v4C;

	//�������� ���� � �������� �������� ��������
	osg::ref_ptr< osg::Node > m_SceneRoot;
};

#endif	//_OSG_ISECTOR_HAT_H_