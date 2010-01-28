#ifndef _UPD_CLBK_MAIN_NODE_H_
#define _UPD_CLBK_MAIN_NODE_H_

#include <osg/NodeCallback>

class UpdClbkMainNode : public osg::NodeCallback
{
public:
	UpdClbkMainNode();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

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

#endif //_UPD_CLBK_MAIN_NODE_H_