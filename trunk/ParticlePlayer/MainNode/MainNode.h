#ifndef _MAIN_NODE_H_
#define _MAIN_NODE_H_

#include "Particle/Particle.h"

#include <osg/ref_ptr>
#include <osg/Group>
#include <osg/Program>

class MainNode : public osg::Referenced
{
public:
	MainNode();
	~MainNode();

	//инициализация данных
	void Init();

	//вернуть главный узел
	osg::ref_ptr< osg::Group > GetNode(){ return m_Group.get(); };

private:
	//добавить шейдер в сцену
	void AddShader( osg::StateSet* ss );

	// load source from a file.
	void LoadShaderSource( osg::Shader* shader, const std::string& fileName );

	//корневой узел
	osg::ref_ptr< osg::Group > m_Group;

	//генератор частиц
	Particle m_Particle;
};

#endif	//_MAIN_NODE_H_