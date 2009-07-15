#include "DynamicTexture.h"
#include <osgViewer/Viewer>

int main()
{
	// construct the viewer.
	osgViewer::Viewer viewer;

	
	//������� ����� � ������������ ���������
	DynamicTexture dynTexture;

	//��������� ������ ������������
	viewer.setSceneData( dynTexture.getRootNode().get() );

	return viewer.run();
}