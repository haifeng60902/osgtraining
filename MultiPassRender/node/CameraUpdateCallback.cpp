#include "CameraUpdateCallback.h"

#include <osg/Camera>

#include <iostream>

float fY = 0.0f;

CameraUpdateCallback::CameraUpdateCallback()
{

}

void CameraUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::Camera* cam = dynamic_cast< osg::Camera* >( node );
	if ( cam )
	{
		osg::Matrix mtTr , mtRtX , mtRtZ;
		mtRtX.makeRotate( osg::DegreesToRadians( -90.0 ) , 1, 0 , 0 );
		mtRtZ.makeRotate( osg::DegreesToRadians( 90.0 ) , 0, 0 , 1 );
		mtTr.makeTranslate( 0 , 0 , fY );

		fY -= 0.001;

		std::cout << fY << " ";

		//задать явно смещение
		cam->setViewMatrix( mtRtZ * mtRtX * mtTr);
	}

	traverse(node,nv);
}