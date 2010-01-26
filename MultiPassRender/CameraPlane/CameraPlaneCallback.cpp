#include "CameraPlaneCallback.h"

#include "CameraState.h"

#include <osg/MatrixTransform>

CameraPlaneCallback::CameraPlaneCallback()
{

}

void CameraPlaneCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);  

	osg::MatrixTransform *mt = dynamic_cast< osg::MatrixTransform* >( node );
	if ( mt )
	{
		//получить доступ к состоянию камеры 
		binCameraState &mCamState = CameraState::Instance().GetCameraState();

		osg::Matrix mtT;
		mtT.makeTranslate( -mCamState.m_dX , -mCamState.m_dY , -mCamState.m_dZ );

		osg::Matrix mtH;
		mtH.makeRotate( osg::DegreesToRadians( -mCamState.m_dH ) , 1 , 0 , 0 );

		osg::Matrix mtR;
		mtR.makeRotate( osg::DegreesToRadians( -mCamState.m_dR ) , 0 , 0 , 1 );

		mt->setMatrix( mtH * mtR * mtT );
	}
}