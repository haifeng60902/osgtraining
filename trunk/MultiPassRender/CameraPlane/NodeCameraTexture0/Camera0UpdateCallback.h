#ifndef _CAMERA_0_UPDATE_CALLBACK_H_
#define _CAMERA_0_UPDATE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Vec3>

class Camera0UpdateCallback : public osg::NodeCallback
{
public:
	Camera0UpdateCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:

	//���������� ��������
	void ProcessRotate();

	//���������� �����������
	void ProcessMove();

	//����������� ������ ������
	void MoveForward();

	//����������� ������ �����
	void MoveBackward();

	osg::Vec3 m_v3Pos;			//������� ������ � 3D ������������
	osg::Vec3 m_v3Rot;			//���� �������� ������ ������ ���� X,Y,Z

	float m_fMoveSpeed;			//�������� ����������� ������
};

#endif	//_CAMERA_0_UPDATE_CALLBACK_H_