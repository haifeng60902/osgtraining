#include "UfoManipulator.h"

using namespace osg;
using namespace osgGA;

#include <iostream>

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
			if (calcMovement()) 
				us.requestRedraw();
			return true;

		case(GUIEventAdapter::RESIZE):
			init(ea,us);
			us.requestRedraw();
			return true;

		default:
			return false;
	}
}

void UfoManipulator::getUsage(osg::ApplicationUsage& usage) const
{
	usage.addKeyboardMouseBinding("Flight: Space","Reset the viewing position to home");
	usage.addKeyboardMouseBinding("Flight: q","Automatically yaw when banked (default)");
	usage.addKeyboardMouseBinding("Flight: a","No yaw when banked");
}

void UfoManipulator::flushMouseEventStack()
{
	m_GaT1 = NULL;
	m_GaT0 = NULL;
}

void UfoManipulator::addMouseEvent(const GUIEventAdapter& ea)
{
	m_GaT1 = m_GaT0;
	m_GaT0 = &ea;
}

void UfoManipulator::computePosition(const osg::Vec3& eye , const osg::Vec3& lv , const osg::Vec3& up )
{
	osg::Vec3 f(lv);
	f.normalize();
	osg::Vec3 s(f^up);
	s.normalize();
	osg::Vec3 u(s^f);
	u.normalize();

	osg::Matrixd rotation_matrix(s[0],     u[0],     -f[0],     0.0f,
		s[1],     u[1],     -f[1],     0.0f,
		s[2],     u[2],     -f[2],     0.0f,
		0.0f,     0.0f,     0.0f,      1.0f);

	m_v3Eye = eye;
	m_fDistance = lv.length();
	m_qRotation = rotation_matrix.getRotate().inverse();
}

bool UfoManipulator::calcMovement()
{
	//_camera->setFusionDistanceMode(osg::Camera::PROPORTIONAL_TO_SCREEN_DISTANCE);

	// return if less then two events have been added.
	if ( m_GaT0.get() == NULL || m_GaT1.get() == NULL )
		return false;


	double dt = m_GaT0->getTime() - m_GaT1->getTime();

	if ( dt < 0.0f )
	{
		notify(INFO) << "warning dt = "<< dt << std::endl;
		dt = 0.0f;
	}

	unsigned int buttonMask = m_GaT1->getButtonMask();
	if ( buttonMask == GUIEventAdapter::LEFT_MOUSE_BUTTON )
		// pan model.
		m_fVelocity += dt * m_fModelScale * 0.05f;

	else 
		if ( buttonMask == GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
				buttonMask == ( GUIEventAdapter::LEFT_MOUSE_BUTTON | GUIEventAdapter::RIGHT_MOUSE_BUTTON ) )
			m_fVelocity = 0.0f;
		else 
			if (buttonMask==GUIEventAdapter::RIGHT_MOUSE_BUTTON)
				m_fVelocity -= dt * m_fModelScale * 0.05f;

	float dx = m_GaT0->getXnormalized();
	float dy = m_GaT0->getYnormalized();

	//std::cout << dx << "\t\t" << dy << "\t\t" << dt << ";\n";
	if ( ( dt < 0.01 ) || ( dt > 0.02 ) )
		std::cout << dt << "\n";

	// osg::notify(osg::NOTICE)<<"dx = "<<dx<<" dy = "<<dy<<"dt = "<<dt<<std::endl;

	// mew - flag to reverse mouse-control mapping
	if( getenv( "OSGHANGGLIDE_REVERSE_CONTROLS" ) )
	{
		dx = -dx;
		dy = -dy;
	}

	osg::Matrixd rotation_matrix;
	rotation_matrix.makeRotate( m_qRotation );

	osg::Vec3 up = osg::Vec3( 0.0f , 1.0f , 0.0 ) * rotation_matrix;
	osg::Vec3 lv = osg::Vec3( 0.0f , 0.0f , -1.0f ) * rotation_matrix;

	osg::Vec3 sv = lv^up;
	sv.normalize();

	float pitch = -inDegrees(dy*75.0f*dt);
	float roll = inDegrees(dx*50.0f*dt);

	osg::Quat delta_rotate;

	osg::Quat roll_rotate;
	osg::Quat pitch_rotate;

	pitch_rotate.makeRotate(pitch,sv.x(),sv.y(),sv.z());
	roll_rotate.makeRotate(roll,lv.x(),lv.y(),lv.z());

	delta_rotate = pitch_rotate*roll_rotate;

	lv *= ( m_fVelocity * dt );

	m_v3Eye += lv;
	m_qRotation = m_qRotation * delta_rotate;

	return true;
}
