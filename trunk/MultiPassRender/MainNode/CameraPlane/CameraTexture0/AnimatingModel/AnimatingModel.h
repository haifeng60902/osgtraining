#ifndef _ANIMATING_MODEL_H_
#define	_ANIMATING_MODEL_H_

#include <osg/MatrixTransform>

#include <string>

//анимированная модель
class AnimatingModel
{
public:
	AnimatingModel();
	~AnimatingModel();

	//загрузить модель
	void Init( std::string sModel );

	//вернуть узел
	osg::ref_ptr< osg::MatrixTransform > GetNode(){ return m_MtrTr.get(); };

private:

	//узел, содержащий анимированную модель
	osg::ref_ptr< osg::MatrixTransform > m_MtrTr;
};

#endif	//_ANIMATING_MODEL_H_