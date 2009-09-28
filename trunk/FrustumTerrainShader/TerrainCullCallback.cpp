#include "TerrainCullCallback.h"

#include "FrustumSingleton.h"

TerrainCullCallback::TerrainCullCallback() : m_bProj( true )
{

}

TerrainCullCallback::~TerrainCullCallback()
{

}

void TerrainCullCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);

	/*
	osgUtil::CullVisitor* cv = dynamic_cast< osgUtil::CullVisitor* >( nv );
	if (cv)
	{
		//������ � ������� �������� ����������� ���� ���
		if ( m_bProj )
		{
			FrustumSingleton::Instance().UpdateProjection( *cv->getProjectionMatrix() );
			m_bProj = false;
		}

		//�������� ��������� ��������� ������
		FrustumSingleton::Instance().UpdateFrustum( osg::Matrix::inverse( *cv->getModelViewMatrix() ) );

		//������ ��������� �����������
		FrustumSingleton::Instance().SetViewPos( cv->getViewPoint() );
	}
	*/
}