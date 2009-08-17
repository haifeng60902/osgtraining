#ifndef _CULL_CALLBACK_H_
#define _CULL_CALLBACK_H_

#include <osg/vec3>
#include <osg/vec4>
#include <osg/Matrix>
#include <osg/NodeCallback>

#include <string>

class CullCallback : public osg::NodeCallback
{
public:
	CullCallback( std::string name );
	~CullCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:

	//обновить информацию о плоскостях отсечения
	void UpdateFrustum( osg::Matrix proj , osg::Matrix mv );

	//Определение видимости BOX'a
	bool BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx );

	// Given a Camera, create a wireframe representation of its
	// view frustum. Create a default representation if camera==NULL.
	osg::Node* makeFrustumFromCamera( osg::Matrixd proj , osg::Matrixd mv );

	//вычислить уравнение плоскости по трем точкам
	osg::Vec4 MakePlane( osg::Vec3 P1 , osg::Vec3 P2 , osg::Vec3 P3 );

	osg::Vec4 plane[6];	// шесть плоскостей, ограничивающих видимый объем

	// Get near and far from the Projection matrix.
	double near;
	double far;

	// Get the sides of the near plane.
	double nLeft;
	double nRight;
	double nTop;
	double nBottom;

	// Get the sides of the far plane.
	double fLeft;
	double fRight;
	double fTop;
	double fBottom;

	osg::Matrix m_iMV;

	//имя callback'a
	std::string m_sCallbackName;
};

#endif	//_CULL_CALLBACK_H_
