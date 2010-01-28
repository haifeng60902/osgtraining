#ifndef _UPDATE_CALLBACK_CAMERA_0_H_
#define _UPDATE_CALLBACK_CAMERA_0_H_

#include <osg/NodeCallback>
#include <osg/Vec3>

class UpdateCallbackCamera0 : public osg::NodeCallback
{
public:
	UpdateCallbackCamera0();

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

	osg::Vec3 m_v3Pos;			//позиция камеры в 3D пространстве
	osg::Vec3 m_v3Rot;			//углы поворота камеры вокруг осей X,Y,Z

	float m_fMoveSpeed;			//скорость перемещения камеры
};

#endif	//_UPDATE_CALLBACK_CAMERA_0_H_