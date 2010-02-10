#ifndef _UPD_CLBK_ANIMATING_MODEL_H_
#define _UPD_CLBK_ANIMATING_MODEL_H_

#include <osg/NodeCallback>

class UpdClbkAnimatingModel : public osg::NodeCallback
{
public:
	UpdClbkAnimatingModel();
	
	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:
	double m_dR;
};

#endif	//_UPD_CLBK_ANIMATING_MODEL_H_