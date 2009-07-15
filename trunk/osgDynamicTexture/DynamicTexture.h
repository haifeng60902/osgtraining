#ifndef _DYNAMIC_TEXTURE_H_
#define _DYNAMIC_TEXTURE_H_

#include <osg/Group>
#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Image>

class DynamicTexture : public osg::Referenced
{
public:
	DynamicTexture();
	~DynamicTexture();

	osg::ref_ptr< osg::Group > getRootNode() { return m_rootNode.get(); }

private:
	/*methods*/
	void buildScene();

	//добавить текстуру
	void AddTexture();

	osg::ref_ptr<osg::Group> m_rootNode;

	osg::ref_ptr<osg::Image> image0;
};

#endif	//_DYNAMIC_TEXTURE_H_