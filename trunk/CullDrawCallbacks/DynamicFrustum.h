#ifndef _DYNAMIC_FRUSTUM_H_
#define _DYNAMIC_FRUSTUM_H_

#include <osg/Node>

#include "Singleton.h"

class DynamicFrustum : public Singleton< DynamicFrustum >
{
public:
	DynamicFrustum();
	~DynamicFrustum();

	//создать фрустум
	void CreateFrustum(){ m_bCreateFrustum = true; };

	//нужно ли создавать фрустум?
	bool IsCreateFrustum();

	//передать узел созданного frustum'a
	void SetNodeFrustum( osg::Node* _pNodeFrustum ){ m_pNodeFrustum = _pNodeFrustum; };

	//получить узел frustum'a
	osg::Node* GetNodeFrustum();

private:
	bool m_bCreateFrustum;

	osg::Node* m_pNodeFrustum;
};

#endif	//_DYNAMIC_FRUSTUM_H_