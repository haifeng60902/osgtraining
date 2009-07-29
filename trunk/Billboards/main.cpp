#include "Billboards.h"

#include <osgViewer/Viewer>
#include <osg/ref_ptr>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	//����� billboard'��
	osg::ref_ptr< Billboards > bill = new Billboards;

	//��������� ������ ������������
	viewer.setSceneData( bill->getRootGroup().get() );

	return viewer.run();
}