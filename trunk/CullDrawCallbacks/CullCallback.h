#ifndef _CULL_CALLBACK_H_
#define _CULL_CALLBACK_H_

#include <osg/vec3>
#include <osg/vec4>
#include <osg/Matrix>
#include <osg/NodeCallback>

class CullCallback : public osg::NodeCallback
{
public:
	CullCallback();
	~CullCallback();

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);

private:

	//�������� ���������� � ���������� ���������
	void UpdateFrustum( const float *clip );

	//����������� ��������� BOX'a
	bool BoxVisible( const osg::Vec3 &minn , const osg::Vec3 &maxx );

	osg::Vec4 plane[6];	// ����� ����������, �������������� ������� ����� 

};

#endif	//_CULL_CALLBACK_H_
