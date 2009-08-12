#ifndef _BRANCH_XML_WIND_CALLBACK_H_
#define _BRANCH_XML_WIND_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Image>

#include <vector>

class BranchXMLWindCallback : public osg::NodeCallback
{
public:
	BranchXMLWindCallback();
	~BranchXMLWindCallback();

	virtual void operator()( osg::Node* node, osg::NodeVisitor* nv );

	//передать вектор uniform матриц
	void SetUniformMatrix( const std::vector< osg::Uniform* > &_vUM ){ m_vUM = _vUM; };

	//задать uniform силы ветра
	void SetUniformWindStrength( osg::Uniform* _wind ){ m_unifWindStrength = _wind; };

	//передать динамически меняемую картинку
	void SetDynamicImage( osg::ref_ptr< osg::Image > img ){ m_Image = img; };

private:
	//обновление матриц ветра
	void SetupWindMatrices(float fTimeInSecs);

	//обновить матрицу в текстуре
	void UpdateTextureMatrix();

	//обновить картинку
	void UpdateImage();

	unsigned char GetRand();

	float GetFloatRand();

	float m_fWindStrength;		// 0.0 = no wind, 1.0 = full strength

	std::vector< std::vector< float > > m_vWM;

	std::vector< osg::Uniform* > m_vUM;

	//сила ветра
	osg::Uniform* m_unifWindStrength;

	//текстура с координатами деревьев
	osg::ref_ptr<osg::Image> m_Image;
};

#endif	//_BRANCH_XML_WIND_CALLBACK_H_