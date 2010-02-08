#include "UpdClbkLightPoint.h"

#include "Lighting.h"

#include <osg/MatrixTransform>

UpdClbkLightPoint::UpdClbkLightPoint() : m_dRot( 0.0 )
{

}

void UpdClbkLightPoint::operator()( osg::Node* node, osg::NodeVisitor* nv)
{
	osg::MatrixTransform* mMatrTr = dynamic_cast< osg::MatrixTransform* >( node );

	if ( mMatrTr )
	{
		osg::Matrix mTr , mR , mF;
		mR.makeRotate( osg::DegreesToRadians( m_dRot ) , 0,0,1 );
		mTr.makeTranslate( 0,4,0 );

		mF = mTr * mR;

		mMatrTr->setMatrix( mF );

		Lighting::Instance().GetLight().m_dX = mF( 3 , 0 );
		Lighting::Instance().GetLight().m_dY = mF( 3 , 1 );
		Lighting::Instance().GetLight().m_dZ = mF( 3 , 2 );

		//m_dRot += 0.1;
	}

	traverse(node,nv);
}