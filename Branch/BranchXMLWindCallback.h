#ifndef _BRANCH_XML_WIND_CALLBACK_H_
#define _BRANCH_XML_WIND_CALLBACK_H_

#include <osg/NodeCallback>
#include "osg/Image"

#include <vector>

class BranchXMLWindCallback : public osg::NodeCallback
{
public:
	BranchXMLWindCallback( osg::Uniform *_wRot , osg::ref_ptr<osg::Image> image0 );
	~BranchXMLWindCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

private:
	//обновление матриц ветра
	void SetupWindMatrices(float fTimeInSecs);

	float m_fWindStrength;		// 0.0 = no wind, 1.0 = full strength

	osg::Uniform *m_wRot;

	std::vector< std::vector< float > > m_vWM;


	osg::ref_ptr<osg::Image> m_Image0;
};

#endif	//_BRANCH_XML_WIND_CALLBACK_H_