#ifndef _UNI_UPD_CLBK_LIGHT_POS_H_
#define _UNI_UPD_CLBK_LIGHT_POS_H_

#include <osg/Uniform>

class UniUpdClbkLightPos : public osg::Uniform::Callback
{
public:
	UniUpdClbkLightPos();

	virtual void operator() ( osg::Uniform* uniform, osg::NodeVisitor* nv );
};

#endif	//_UNI_UPD_CLBK_LIGHT_POS_H_