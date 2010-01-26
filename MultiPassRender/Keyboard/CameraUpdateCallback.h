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

	//обработать вращения
	void ProcessRotate();

	//обработать перемещение
	void ProcessMove();

	//перемещение камеры вперед
	void MoveForward();

	//перемещение камеры назад
	void MoveBackward();

	float m_fMoveSpeed;			//скорость перемещения камеры
};

#endif	//_CAMERA_UPDATE_CALLBACK_H_