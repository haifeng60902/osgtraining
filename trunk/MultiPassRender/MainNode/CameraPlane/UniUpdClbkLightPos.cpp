#include "UniUpdClbkLightPos.h"

#include "Lighting.h"

UniUpdClbkLightPos::UniUpdClbkLightPos()
{

}

void UniUpdClbkLightPos::operator()( osg::Uniform* uniform, osg::NodeVisitor* nv )
{
	//�������� ����� �������� ��������� ��������� �����
	uniform->set( osg::Vec4( Lighting::Instance().GetLight().m_dX , 
		Lighting::Instance().GetLight().m_dY ,
		Lighting::Instance().GetLight().m_dZ , 
		1.0 ) );
}