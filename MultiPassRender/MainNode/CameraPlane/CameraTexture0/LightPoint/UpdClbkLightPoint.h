#ifndef _UPD_CLBK_LIGHT_POINT_H_
#define _UPD_CLBK_LIGHT_POINT_H_

#include <osg/NodeCallback>

class UpdClbkLightPoint : public osg::NodeCallback
{
public:
	UpdClbkLightPoint();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:

	double m_dRot;
};

#endif	//_UPD_CLBK_LIGHT_POINT_H_