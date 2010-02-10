#ifndef _ANIMATING_MODEL_H_
#define	_ANIMATING_MODEL_H_

#include <osg/MatrixTransform>

#include <string>

//������������� ������
class AnimatingModel
{
public:
	AnimatingModel();
	~AnimatingModel();

	//��������� ������
	void Init( std::string sModel );

	//������� ����
	osg::ref_ptr< osg::MatrixTransform > GetNode(){ return m_MtrTr.get(); };

private:

	//����, ���������� ������������� ������
	osg::ref_ptr< osg::MatrixTransform > m_MtrTr;
};

#endif	//_ANIMATING_MODEL_H_