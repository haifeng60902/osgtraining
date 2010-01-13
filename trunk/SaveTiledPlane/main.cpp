#include "osgTiledPlane.h"

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

int main()
{
	//�������� ������ ������ �����������
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFile( "ball.osg" );
	osgTiledPlane plane;

	bool res = osgDB::writeNodeFile( *plane.GetNode() , "plane.osg" ); 
}