#ifndef _DYNAMIC_FRUSTUM_H_
#define _DYNAMIC_FRUSTUM_H_

#include <osg/Node>

#include "Singleton.h"

class DynamicFrustum : public Singleton< DynamicFrustum >
{
public:
	DynamicFrustum();
	~DynamicFrustum();

	//������� �������
	void CreateFrustum(){ m_bCreateFrustum = true; };

	//����� �� ��������� �������?
	bool IsCreateFrustum();

	//�������� ���� ���������� frustum'a
	void SetNodeFrustum( osg::Node* _pNodeFrustum ){ m_pNodeFrustum = _pNodeFrustum; };

	//�������� ���� frustum'a
	osg::Node* GetNodeFrustum();

private:
	bool m_bCreateFrustum;

	osg::Node* m_pNodeFrustum;
};

#endif	//_DYNAMIC_FRUSTUM_H_