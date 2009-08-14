#include "CullCallback.h"

#include <osgUtil/CullVisitor>

#include <iostream>

CullCallback::CullCallback()
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
		osg::Matrix mvp = ( *MV ) * ( *Pr );

		//обновить информацию о плоскостях отсечения
		UpdateFrustum( (float*)mvp.ptr() );

		osg::Vec3 pos = cv->getEyePoint();
		std::cout << pos.x() << " " 
			<< pos.y() << " " 
			<< pos.z() << " " 
			<<  "\n";

		/*
		if ( BoxVisible( osg::Vec3(-1,-1,-1) , osg::Vec3(1,1,1) ) )
			std::cout << "1 ";
		else
			std::cout << "0 ";
*/
	}
}

void CullCallback::UpdateFrustum( const float *clip )
{
	float t = 0.0f;

	//обновить информацию о плоскостях отсечения
	plane[0].x() = clip[ 3] -	clip[ 0];			//Извлечение из матрицы clip
	plane[0].y() = clip[ 7] - clip[ 4];			//уравнений шести плоскотей отсечения
	plane[0].z() = clip[11] - clip[ 8]; 
	plane[0].w() = clip[15] - clip[12]; 
	t = 1.0 / sqrt( plane[0].x() * plane[0].x()
		+ plane[0].y() * plane[0].y()
		+ plane[0].z() * plane[0].z() ); 

	plane[0].x() *= t; 
	plane[0].y() *= t; 
	plane[0].z() *= t; 
	plane[0].w() *= t; 

	plane[1].x() = clip[ 3] + clip[ 0]; 
	plane[1].y() = clip[ 7] + clip[ 4]; 
	plane[1].z() = clip[11] + clip[ 8]; 
	plane[1].w() = clip[15] + clip[12]; 
	t = 1.0 / sqrt( plane[1].x() * plane[1].x()
		+ plane[1].y() * plane[1].y()
		+ plane[1].z() * plane[1].z() ); 
	
	plane[1].x() *= t; 
	plane[1].y() *= t; 
	plane[1].z() *= t; 
	plane[1].w() *= t; 

	plane[2].x() = clip[ 3] + clip[ 1]; 
	plane[2].y() = clip[ 7] + clip[ 5]; 
	plane[2].z() = clip[11] + clip[ 9]; 
	plane[2].w() = clip[15] + clip[13]; 
	t = 1.0 / sqrt( plane[2].x() * plane[2].x() 
		+ plane[2].y() * plane[2].y() 
		+ plane[2].z() * plane[2].z() ); 

	plane[2].x() *= t; 
	plane[2].y() *= t; 
	plane[2].z() *= t; 
	plane[2].w() *= t; 

	plane[3].x() = clip[ 3] - clip[ 1]; 
	plane[3].y() = clip[ 7] - clip[ 5]; 
	plane[3].z() = clip[11] - clip[ 9]; 
	plane[3].w() = clip[15] - clip[13]; 
	t = 1.0 / sqrt( plane[3].x() * plane[3].x() 
		+ plane[3].y() * plane[3].y() 
		+ plane[3].z() * plane[3].z() ); 
	plane[3].x() *= t; 
	plane[3].y() *= t; 
	plane[3].z() *= t; 
	plane[3].w() *= t; 

	plane[4].x() = clip[ 3] - clip[ 2]; 
	plane[4].y() = clip[ 7] - clip[ 6]; 
	plane[4].z() = clip[11] - clip[10]; 
	plane[4].w() = clip[15] - clip[14]; 
	t = 1.0 / sqrt( plane[4].x() * plane[4].x() 
		+ plane[4].y() * plane[4].y() 
		+ plane[4].z() * plane[4].z() );
	plane[4].x() *= t; 
	plane[4].y() *= t; 
	plane[4].z() *= t; 
	plane[4].w() *= t; 

	plane[5].x() = clip[ 3] + clip[ 2]; 
	plane[5].y() = clip[ 7] + clip[ 6]; 
	plane[5].z() = clip[11] + clip[10]; 
	plane[5].w() = clip[15] + clip[14]; 
	t = 1.0 / sqrt( plane[5].x() * plane[5].x()
		+ plane[5].y() * plane[5].y() 
		+ plane[5].z() * plane[5].z() );

	plane[5].x() *= t; 
	plane[5].y() *= t; 
	plane[5].z() *= t; 
	plane[5].w() *= t; 
}

bool CullCallback::BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx )
{
	//Определение видимости BOX'a
	for(int i = 0; i < 6; i++) {
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