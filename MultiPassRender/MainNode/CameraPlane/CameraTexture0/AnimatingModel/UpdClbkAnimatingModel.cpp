#include "UpdClbkAnimatingModel.h"

#include <osg/MatrixTransform>

UpdClbkAnimatingModel::UpdClbkAnimatingModel() : m_dR( 0.0 )
{

}

void UpdClbkAnimatingModel::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	osg::MatrixTransform* pMtrTr = dynamic_cast< osg::MatrixTransform* >( node );
	if ( pMtrTr )
	{
		osg::Matrix mT , mRz;

		mRz.makeRotate( osg::DegreesToRadians( m_dR ) , 0,0,1 );
		mT.makeTranslate( m_dR * 0.01 ,0,0 );

		pMtrTr->setMatrix( mT * mRz );

		m_dR += 0.1;
	}

	traverse(node,nv);
}