#ifndef _OSG_ISECTOR_HAT_H_
#define _OSG_ISECTOR_HAT_H_

#include <osg/Referenced>
#include <osg/ref_ptr>
#include <osg/Switch>


class osgIsectorHAT : public osg::Referenced
{
public:
	osgIsectorHAT();

	//откуда начинать тестировать
	void setTarget( osg::ref_ptr< osg::Node > _node ){ m_SceneRoot = _node; };

	//включение isector'a
	void setEnable( bool _bEnable ){ m_bEnable = _bEnable; };

	//внешняя стратегия перемещения
	void setPositionReference( osg::ref_ptr< osg::MatrixTransform > _mt );

	//включить режим отображения линии isector'a
	void setRenderEnable( bool _bEnable );

	//размер isector'a
	void setSegmentZExtent( float _dMinZ , float _dMaxZ );

	//узнать высоту пересечения
	float GetHAT();

private:
	
	//создание линии для отладочных целей
	void InitLine();

	//включение isector'a
	bool m_bEnable;

	//режим отображения isector'a
	bool m_bRender;

	//osg::Switch для включения/выключения отображения isector'a
	osg::ref_ptr< osg::Switch > m_Switch;

	//вершины линии
	osg::ref_ptr<osg::Vec3Array> m_v3V;

	//цвет линии
	osg::ref_ptr<osg::Vec4Array> m_v4C;

	//корневой узел с которого начинать проверку
	osg::ref_ptr< osg::Node > m_SceneRoot;
};

#endif	//_OSG_ISECTOR_HAT_H_