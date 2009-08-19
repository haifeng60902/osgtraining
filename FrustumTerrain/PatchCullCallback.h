#ifndef _PATCH_CULL_CALLBACK_H_ 
#define _PATCH_CULL_CALLBACK_H_

#include <osg/NodeCallback>

class PatchCullCallback : public osg::NodeCallback
{
public:
	PatchCullCallback();
	~PatchCullCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

};

#endif	//_PATCH_CULL_CALLBACK_H_