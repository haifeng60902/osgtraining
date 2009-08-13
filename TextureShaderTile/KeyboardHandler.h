#ifndef _KEYBOARD_HANDLER_H_
#define _KEYBOARD_HANDLER_H_

#include <osgGA/GUIEventHandler>

class KeyboardHandler : public osgGA::GUIEventHandler 
{
public:
	KeyboardHandler();
	~KeyboardHandler();

	bool handle( const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa );

	//передать Uniform смещения
	void SetOffsetX( osg::ref_ptr< osg::Uniform > _OffsetX ){ m_OffsetX = _OffsetX; };
	void SetOffsetY( osg::ref_ptr< osg::Uniform > _OffsetY ){ m_OffsetY = _OffsetY; };

	//передать Uniform масштабирования
	void SetScaleX( osg::ref_ptr< osg::Uniform > _ScaleX ){ m_ScaleX = _ScaleX; };
	void SetScaleY( osg::ref_ptr< osg::Uniform > _ScaleY ){ m_ScaleY = _ScaleY; };

	void SetOffsetScaleX( osg::ref_ptr< osg::Uniform > _OffsetScaleX ){ m_OffsetScaleX = _OffsetScaleX; };
	void SetOffsetScaleY( osg::ref_ptr< osg::Uniform > _OffsetScaleY ){ m_OffsetScaleY = _OffsetScaleY; };

private:
	osg::ref_ptr< osg::Uniform > m_OffsetX;
	osg::ref_ptr< osg::Uniform > m_OffsetY;

	osg::ref_ptr< osg::Uniform > m_ScaleX;
	osg::ref_ptr< osg::Uniform > m_ScaleY;

	osg::ref_ptr< osg::Uniform > m_OffsetScaleX;
	osg::ref_ptr< osg::Uniform > m_OffsetScaleY;

	float m_fOffsetX;
	float m_fOffsetY;

	float m_fScaleX;
	float m_fScaleY;

	float m_fOffsetScaleX;
	float m_fOffsetScaleY;
};

#endif	//_KEYBOARD_HANDLER_H_