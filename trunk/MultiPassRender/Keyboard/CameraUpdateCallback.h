#ifndef _CAMERA_UPDATE_CALLBACK_H_
#define _CAMERA_UPDATE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Vec3>

class CameraUpdateCallback : public osg::NodeCallback
{
public:
	CameraUpdateCallback();

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

	float m_fMoveSpeed;			//�������� ����������� ������
};

#endif	//_CAMERA_UPDATE_CALLBACK_H_