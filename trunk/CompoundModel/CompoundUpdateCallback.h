#ifndef _COMPOUND_UPDATE_CALLBACK_H_ 
#define _COMPOUND_UPDATE_CALLBACK_H_

#include <osg/NodeCallback>
#include <osg/Image>

class CompoundUpdateCallback : public osg::NodeCallback
{
public:
	CompoundUpdateCallback();
	~CompoundUpdateCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

	//�������� ����������� �������� ��������
	void SetDynamicImage( osg::ref_ptr< osg::Image > img ){ m_Image = img; };

private:

	//�������� ��������
	void UpdateImage();

	float GetFloatRand();

	//�������� � ������������ ���������������� ������
	osg::ref_ptr<osg::Image> m_Image;
};

#endif	//_COMPOUND_UPDATE_CALLBACK_H_