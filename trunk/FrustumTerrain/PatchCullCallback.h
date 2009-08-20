#ifndef _PATCH_CULL_CALLBACK_H_ 
#define _PATCH_CULL_CALLBACK_H_

#include "VisiblePatchArray.h"

#include <osg/NodeCallback>
#include <osg/Image>

class PatchCullCallback : public osg::NodeCallback
{
public:
	PatchCullCallback();
	~PatchCullCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

	//передать динамически меняемую картинку
	void SetDynamicImage( osg::ref_ptr< osg::Image > img ){ m_Image = img; };

private:

	//обновить картинку
	void UpdateImage();

	float GetFloatRand();

	//класс формирующий массив видимых патчей
	VisiblePatchArray m_VisiblePatchArray;

	//текстура с координатами позиционирования патчей
	osg::ref_ptr<osg::Image> m_Image;
};

#endif	//_PATCH_CULL_CALLBACK_H_