#include "Forest.h"

#include "BranchXML.h"
#include "FrondsXML.h"

Forest::Forest()
{
	m_rootNode = new osg::Group;

	//инициализировать стволы
	InitBranches();

	//инициализировать ветки леса
	InitFronds();
}

Forest::~Forest()
{

}

void Forest::InitBranches()
{
	//инициализировать стволы

	//инициализировать ствол
	osg::ref_ptr< BranchXML > branch = new BranchXML;

	for ( int i = 0 ; i < 20 ; ++i )
		for ( int j = 0 ; j < 20 ; ++j )
		{
			//создать узел, содержащий ствол
			osg::ref_ptr< osg::Group > tree = new osg::Group;
			
			osg::StateSet *ss = tree->getOrCreateStateSet();

			//добавить геометрию ствола в узел
			tree->addChild( branch->getBranchGeode().get() );

			//добавить узел с геометрией ствола и смещением в общий лес
			m_rootNode->addChild( tree.get() );

			//задать положение через uniform
			SetPos( ss , i * 100.0 , j * 100.0 );
		}
}

void Forest::InitFronds()
{
	//инициализировать ветки леса
	
	//инициализировать ветки
	osg::ref_ptr< FrondsXML > fronds = new FrondsXML;

	for ( int i = 0 ; i < 20 ; ++i )
		for ( int j = 0 ; j < 20 ; ++j )
		{
			//создать узел, содержащий ствол
			osg::ref_ptr< osg::Group > tree = new osg::Group;

			osg::StateSet *ss = tree->getOrCreateStateSet();

			//добавить геометрию ствола в узел
			tree->addChild( fronds->getFrondsGeode().get() );

			//добавить узел с геометрией ствола и смещением в общий лес
			m_rootNode->addChild( tree.get() );

			//задать положение через uniform
			SetPos( ss , i * 100.0 , j * 100.0 );
		}
}

void Forest::SetPos( osg::StateSet *ss , float i , float j )
{
	//задать положение через uniform

	osg::ref_ptr< osg::Uniform > posOffset = new osg::Uniform( "posOffset" , osg::Vec3( j , i , 0.0 ) );
	ss->addUniform( posOffset.get() );
}
