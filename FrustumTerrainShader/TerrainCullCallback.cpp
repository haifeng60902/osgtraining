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
		//данные о матрице проекции обновляются один раз
		if ( m_bProj )
		{
			FrustumSingleton::Instance().UpdateProjection( *cv->getProjectionMatrix() );
			m_bProj = false;
		}

		//обновить плоскости отсечения камеры
		FrustumSingleton::Instance().UpdateFrustum( osg::Matrix::inverse( *cv->getModelViewMatrix() ) );

		//задать положение наблюдателя
		FrustumSingleton::Instance().SetViewPos( cv->getViewPoint() );
	}
	*/
}