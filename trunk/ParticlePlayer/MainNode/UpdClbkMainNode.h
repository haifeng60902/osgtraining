#ifndef _UPD_CLBK_MAIN_NODE_H_
#define _UPD_CLBK_MAIN_NODE_H_

#include <osg/NodeCallback>

class UpdClbkMainNode : public osg::NodeCallback
{
public:
	UpdClbkMainNode();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

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

#endif //_UPD_CLBK_MAIN_NODE_H_