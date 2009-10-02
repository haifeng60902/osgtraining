#include "CollisionDetectionScene.h"

#include "Mi17UpdClbk.h"

#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osg/MatrixTransform>

CollisionDetectionScene::CollisionDetectionScene()
{
	// the root of our scenegraph.
	m_rootNode = new osg::Group;

	//добавить модель земной поверхности
	AddModelTerrain();

	//добавить модель вертолета
	AddModelMi17();

	// Disable lighting in the root node's StateSet. Make
	//   it PROTECTED to prevent osgviewer from enabling it.
	osg::StateSet* state = m_rootNode->getOrCreateStateSet();
	state->setMode( GL_LIGHTING,
		osg::StateAttribute::OFF |
		osg::StateAttribute::OVERRIDE );
}

void CollisionDetectionScene::AddModelTerrain()
{
	//добавить модель земной поверхности
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFile( 
		"C:/Presagis/resources/data/databases/camp_pendleton/camp_pendleton.flt" );

	//статический узел
	root->setDataVariance( osg::Object::STATIC );

	//назначить имя узлу
	root->setName( "camp_pendleton" );

	m_rootNode->addChild( root.get() );
}

void CollisionDetectionScene::AddModelMi17()
{
	//добавить модель вертолета

	//добавить модель
	osg::ref_ptr<osg::Node> root = osgDB::readNodeFile( "Flt/mi17/MI_17_lod.flt" );

	//матрица трансформации для перемещения вертолета
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;

	osg::Matrix m;
	m.makeTranslate( osg::Vec3( 0.f, 0.f, 100.f ) );
	mt->setMatrix( m );

	mt->addChild( root.get() );

	//задать обратный вызов обновления для перемещения модели
	mt->setUpdateCallback( new Mi17UpdClbk );

	//динамический узел
	mt->setDataVariance( osg::Object::DYNAMIC );

	//добавить isector
	AddIsecHAT( mt.get() );

	m_rootNode->addChild( mt.get() );
}

void CollisionDetectionScene::AddIsecHAT( osg::ref_ptr<osg::MatrixTransform> _mt )
{
	for ( int i = 0 ; i < 10 ; ++i )
		for ( int j = 0 ; j < 10 ; ++j )
		{
			//матрица трансформации для перемещения вертолета
			osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;

			osg::Matrix m;
			m.makeTranslate( osg::Vec3( i * 2.0f , j * 2.0f , 0.f ) );
			mt->setMatrix( m );

			//добавить isector
			osg::ref_ptr< osgIsectorHAT > isecHAT = new osgIsectorHAT;
			isecHAT->setTarget( m_rootNode.get() );
			isecHAT->setEnable( true );
			isecHAT->setPositionReference( mt.get() );
			isecHAT->setRenderEnable( true );
			isecHAT->setSegmentZExtent( -200.0 , 200 );

			_mt->addChild( mt.get() );

			//добавить в список очередной isec
			m_lIsecHAT.push_back( isecHAT.get() );
		}
}