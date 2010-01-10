#include "UfoManipulator.h"

UfoManipulator::UfoManipulator()
{
	m_fModelScale = 0.01f;
	m_fVelocity = 0.2f;
	
	m_fDistance = 1.0f;
}

UfoManipulator::~UfoManipulator()
{
}

void UfoManipulator::setByMatrix(const osg::Matrixd& matrix)
{
	m_v3Eye = matrix.getTrans();
	m_qRotation = matrix.getRotate();
	m_fDistance = 1.0f;
}

osg::Matrixd UfoManipulator::getMatrix() const
{
	return osg::Matrixd::rotate( m_qRotation ) * 
		osg::Matrixd::translate( m_v3Eye );
}

osg::Matrixd UfoManipulator::getInverseMatrix() const
{
	return osg::Matrixd::translate( -m_v3Eye ) * 
		osg::Matrixd::rotate( m_qRotation.inverse() );
}

void UfoManipulator::setNode(osg::Node* node)
{
	m_Node = node;
	if ( m_Node.get() )
	{
		const osg::BoundingSphere& boundingSphere = m_Node->getBound();
		m_fModelScale = boundingSphere._radius;
	}
}

const osg::Node* UfoManipulator::getNode() const
{
	return m_Node.get();
}



osg::Node* UfoManipulator::getNode()
{
	return m_Node.get();
}

void UfoManipulator::home( const GUIEventAdapter& ea , GUIActionAdapter& us )
{
	if( m_Node.get() )
	{
		const osg::BoundingSphere& boundingSphere = m_Node->getBound();

		osg::Vec3 v3Eye = osg::Vec3( 0.0f , 0.0f , 0.0f );

		computePosition( v3Eye ,
			osg::Vec3(1.0f,1.0f,-0.1f),
			osg::Vec3(0.0f,0.0f,1.0f));

		m_fVelocity = 0.0f;

		us.requestRedraw();

		us.requestWarpPointer( ( ea.getXmin() + ea.getXmax() ) / 2.0f ,
			( ea.getYmin() + ea.getYmax() ) / 2.0f );

		flushMouseEventStack();
	}
}

void UfoManipulator::init( const GUIEventAdapter& ea , 
						  GUIActionAdapter& us )
{
	flushMouseEventStack();

	us.requestContinuousUpdate( false );

	m_fVelocity = 0.0f;

	if ( ea.getEventType() != GUIEventAdapter::RESIZE )
	{
		us.requestWarpPointer( ( ea.getXmin() + ea.getXmax() ) / 2.0f ,
			( ea.getYmin() + ea.getYmax() ) / 2.0f );
	}
}

bool UfoManipulator::handle( const GUIEventAdapter& ea , GUIActionAdapter& us )
{
	switch(ea.getEventType())
	{
		case(GUIEventAdapter::KEYDOWN):
			if (ea.getKey()==' ')
			{
				flushMouseEventStack();
				home( ea , us );
				us.requestRedraw();
				us.requestContinuousUpdate(false);
				return true;
			}
		case(GUIEventAdapter::FRAME):
			addMouseEvent(ea);
			if (calcMovement()) us.requestRedraw();
			return true;

		case(GUIEventAdapter::RESIZE):
			init(ea,us);
			us.requestRedraw();
			return true;

		default:
			return false;
	}
}
