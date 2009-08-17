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

	//передать геометрию для отрисовки
	void SetGeometry( osg::ref_ptr<osg::Geometry> geom ){ _geometry = geom; };

	//передать uniform смещения
	void SetUniformOffset( osg::ref_ptr< osg::Uniform > _uOffset ){ m_uOffset = _uOffset; } ;

private:
	//геометрия для отрисовки
	osg::ref_ptr<osg::Geometry> _geometry;

	//смещение геометрии
	osg::ref_ptr< osg::Uniform > m_uOffset;
};

#endif	//_DRAW_CALLBACK_H_