#ifndef _DYNAMIC_TEXTURE_CALLBACK_H_
#define _DYNAMIC_TEXTURE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Image>

class DynamicTextureCallback : public osg::NodeCallback
{
public:

	DynamicTextureCallback( osg::ref_ptr<osg::Image> image );

	~DynamicTextureCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:

	unsigned char GetRand();

	osg::ref_ptr<osg::Image> image0;
};

#endif	//_DYNAMIC_TEXTURE_CALLBACK_H_