#ifndef _MI17_UPD_CLBK_H_
#define _MI17_UPD_CLBK_H_

#include <osg/NodeCallback>

#include <vector>

class Mi17UpdClbk : public osg::NodeCallback
{
public:
	Mi17UpdClbk();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	
	double m_dAngle;
	double m_dAdd;
};

#endif	_MI17_UPD_CLBK_H_
