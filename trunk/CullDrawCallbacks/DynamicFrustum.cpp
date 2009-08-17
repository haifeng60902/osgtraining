#include "DynamicFrustum.h"

DynamicFrustum::DynamicFrustum() : m_bCreateFrustum( false )
, m_pNodeFrustum( NULL )
{

}

DynamicFrustum::~DynamicFrustum()
{

}

bool DynamicFrustum::IsCreateFrustum()
{
	//нужно ли создавать фрустум?
	if ( m_bCreateFrustum )
	{
		m_bCreateFrustum = false;
		return true;
	}

	return false;
}

osg::Node* DynamicFrustum::GetNodeFrustum()
{
	//получить узел frustum'a

	if ( m_pNodeFrustum )
	{
		osg::Node *tNode = m_pNodeFrustum;
		m_pNodeFrustum = NULL;
		return tNode;
	}

	return NULL;
}