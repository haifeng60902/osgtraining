#ifndef _DRAW_CALLBACK_H_
#define _DRAW_CALLBACK_H_

#include <osg/Drawable>
#include <osg/Geometry>

class DrawCallback : public osg::Drawable::DrawCallback
{
public:

	DrawCallback();

	virtual ~DrawCallback();

	virtual void drawImplementation( osg::RenderInfo& renderInfo , const osg::Drawable* drawable ) const;

	//�������� ��������� ��� ���������
	void SetGeometry( osg::ref_ptr<osg::Geometry> geom ){ _geometry = geom; };

	//�������� uniform ��������
	void SetUniformOffset( osg::ref_ptr< osg::Uniform > _uOffset ){ m_uOffset = _uOffset; } ;

private:
	//��������� ��� ���������
	osg::ref_ptr<osg::Geometry> _geometry;

	//�������� ���������
	osg::ref_ptr< osg::Uniform > m_uOffset;
};

#endif	//_DRAW_CALLBACK_H_