#include "CullCallback.h"

#include "DynamicFrustum.h"

#include <osgUtil/CullVisitor>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/MatrixTransform>

#include <iostream>

CullCallback::CullCallback( std::string name ) : m_sCallbackName( name )
{

}

CullCallback::~CullCallback()
{

}

void CullCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{ 
	
	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);

	osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
	if (cv)
	{
		const osg::Matrix *MV = cv->getModelViewMatrix();
		const osg::Matrix *Pr = cv->getProjectionMatrix();
		osg::Matrix mvp =  osg::Matrixd::inverse( *MV ) * ( *Pr );

		//обновить информацию о плоскостях отсечения
		UpdateFrustum( *Pr , *MV );

		/*
		if ( BoxVisible( osg::Vec3(-1,-1,-1) , osg::Vec3(1,1,1) ) )
			std::cout << "1 ";
		else
			std::cout << "0 ";
		*/
		std::cout << MV->operator()(3,0) << " "
			<< MV->operator()(3,1) << " "
			<< MV->operator()(3,2) << "\n";

		//нужно ли создавать фрустум?
		bool bFrustum = DynamicFrustum::Instance().IsCreateFrustum();

		if ( bFrustum )
		{
			osg::Node *frustum = makeFrustumFromCamera( *Pr , *MV );

			osg::Group *group = dynamic_cast< osg::Group * >( node );

			if ( group )
			{
				group->addChild( frustum );
			}
		}
		
	}
}

void CullCallback::UpdateFrustum( osg::Matrix proj , osg::Matrix mv )
{
	//Get near and far from the Projection matrix.
	near = proj(3,2) / (proj(2,2)-1.0);
	far = proj(3,2) / (1.0+proj(2,2));

	// Get the sides of the near plane.
	nLeft = near * (proj(2,0)-1.0) / proj(0,0);
	nRight = near * (1.0+proj(2,0)) / proj(0,0);
	nTop = near * (1.0+proj(2,1)) / proj(1,1);
	nBottom = near * (proj(2,1)-1.0) / proj(1,1);

	// Get the sides of the far plane.
	fLeft = far * (proj(2,0)-1.0) / proj(0,0);
	fRight = far * (1.0+proj(2,0)) / proj(0,0);
	fTop = far * (1.0+proj(2,1)) / proj(1,1);
	fBottom = far * (proj(2,1)-1.0) / proj(1,1);

	// Our vertex array needs only 9 vertices: The origin, and the
	// eight corners of the near and far planes.
	osg::Vec3Array* v = new osg::Vec3Array;
	v->resize( 8 );

	(*v)[0].set( nLeft, nBottom, -near );
	(*v)[1].set( nRight, nBottom, -near );
	(*v)[2].set( nRight, nTop, -near );
	(*v)[3].set( nLeft, nTop, -near );
	(*v)[4].set( fLeft, fBottom, -far );
	(*v)[5].set( fRight, fBottom, -far );
	(*v)[6].set( fRight, fTop, -far );
	(*v)[7].set( fLeft, fTop, -far );

	osg::Matrix mt = osg::Matrix::inverse( mv );

	for ( int i = 0 ; i < 8 ; ++i )
		(*v)[i] = (*v)[i] * mt;

	//левая плоскость отсечения
	plane[0] = MakePlane( (*v)[0] , (*v)[7] , (*v)[3] );

	//правая плоскость отсечения
	plane[1] = MakePlane( (*v)[1] , (*v)[2] , (*v)[6] );

	//верхняя плоскость
	plane[2] = MakePlane( (*v)[2] , (*v)[3] , (*v)[7] );

	//нижняя плоскость
	plane[3] = MakePlane( (*v)[0] , (*v)[1] , (*v)[4] );

	//ближняя плоскость
	plane[4] = MakePlane( (*v)[0] , (*v)[2] , (*v)[1] );

	//дальняя плоскость
	plane[5] = MakePlane( (*v)[5] , (*v)[6] , (*v)[7] );
}

bool CullCallback::BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx )
{
	//Определение видимости BOX'a
	for( int i = 0 ; i < 6 ; i++ )
	{
		if( plane[i] * osg::Vec4( minn.x() , minn.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( minn.x() , minn.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( minn.x() , maxx.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( minn.x() , maxx.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , minn.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , minn.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , maxx.y() , minn.z() , 1.0 ) > 0.0 ) continue;
		if( plane[i] * osg::Vec4( maxx.x() , maxx.y() , maxx.z() , 1.0 ) > 0.0 ) continue;
		
		return false;
	}
	return true;
}

// Given a Camera, create a wireframe representation of its
// view frustum. Create a default representation if camera==NULL.
osg::Node* CullCallback::makeFrustumFromCamera( osg::Matrixd proj , osg::Matrixd mv )
{
	// Projection and ModelView matrices

	// Get near and far from the Projection matrix.
	near = proj(3,2) / (proj(2,2)-1.0);
	far = proj(3,2) / (1.0+proj(2,2));

	// Get the sides of the near plane.
	nLeft = near * (proj(2,0)-1.0) / proj(0,0);
	nRight = near * (1.0+proj(2,0)) / proj(0,0);
	nTop = near * (1.0+proj(2,1)) / proj(1,1);
	nBottom = near * (proj(2,1)-1.0) / proj(1,1);

	// Get the sides of the far plane.
	fLeft = far * (proj(2,0)-1.0) / proj(0,0);
	fRight = far * (1.0+proj(2,0)) / proj(0,0);
	fTop = far * (1.0+proj(2,1)) / proj(1,1);
	fBottom = far * (proj(2,1)-1.0) / proj(1,1);

	// Our vertex array needs only 9 vertices: The origin, and the
	// eight corners of the near and far planes.
	osg::Vec3Array* v = new osg::Vec3Array;
	v->resize( 9 );
	(*v)[0].set( 0., 0., 0. );
	(*v)[1].set( nLeft, nBottom, -near );
	(*v)[2].set( nRight, nBottom, -near );
	(*v)[3].set( nRight, nTop, -near );
	(*v)[4].set( nLeft, nTop, -near );
	(*v)[5].set( fLeft, fBottom, -far );
	(*v)[6].set( fRight, fBottom, -far );
	(*v)[7].set( fRight, fTop, -far );
	(*v)[8].set( fLeft, fTop, -far );

	std::cout << nLeft << " "
		<< nRight << " "
		<< nBottom << " "
		<< nTop << " "
		<< near << " "
		<< far << "\n";

	osg::Geometry* geom = new osg::Geometry;
	geom->setUseDisplayList( false );
	geom->setVertexArray( v );

	osg::Vec4Array* c = new osg::Vec4Array;
	c->push_back( osg::Vec4( 1., 1., 1., 1. ) );
	geom->setColorArray( c );
	geom->setColorBinding( osg::Geometry::BIND_OVERALL );

	GLushort idxLines[8] = {
		0, 5, 0, 6, 0, 7, 0, 8 };

	GLushort idxLoops0[4] = {
		1, 2, 3, 4 };

	GLushort idxLoops1[4] = {
		5, 6, 7, 8 };

	geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINES, 8, idxLines ) );
	geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 4, idxLoops0 ) );
	geom->addPrimitiveSet( new osg::DrawElementsUShort( osg::PrimitiveSet::LINE_LOOP, 4, idxLoops1 ) );

	osg::Geode* geode = new osg::Geode;
	geode->addDrawable( geom );

	geode->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED );


	// Create parent MatrixTransform to transform the view volume by
	// the inverse ModelView matrix.
	osg::MatrixTransform* mt = new osg::MatrixTransform;
	mt->setMatrix( osg::Matrixd::inverse( mv ) );
	mt->addChild( geode );

	return mt;
}

osg::Vec4 CullCallback::MakePlane( osg::Vec3 P1 , osg::Vec3 P2 , osg::Vec3 P3 )
{
	//вычислить уравнение плоскости по трем точкам
	osg::Vec4 plane;

	//  A = y1 (z2 - z3) + y2 (z3 - z1) + y3 (z1 - z2)
	plane.x() = P1.y() * ( P2.z() - P3.z() ) + P2.y() * ( P3.z() - P1.z() ) + P3.y() * ( P1.z() - P2.z() );

	//	B = z1 (x2 - x3) + z2 (x3 - x1) + z3 (x1 - x2) 
	plane.y() = P1.z() * ( P2.x() - P3.x() ) + P2.z() * ( P3.x() - P1.x() ) + P3.z() * ( P1.x() - P2.x() );

	//	C = x1 (y2 - y3) + x2 (y3 - y1) + x3 (y1 - y2)
	plane.z() = P1.x() * ( P2.y() - P3.y() ) + P2.x() * ( P3.y() - P1.y() ) + P3.x() * ( P1.y() - P2.y() );

	//	- D = x1 (y2 z3 - y3 z2) + x2 (y3 z1 - y1 z3) + x3 (y1 z2 - y2 z1)
	plane.w() = -P1.x() * ( P2.y() * P3.z() - P3.y() * P2.z() ) 
		- P2.x() * ( P3.y() * P1.z() - P1.y() * P3.z() )
		- P3.x() * ( P1.y() * P2.z() - P2.y() * P1.z() );

	return plane;
}