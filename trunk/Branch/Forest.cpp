#include "Forest.h"

#include "BranchXML.h"
#include "FrondsXML.h"

Forest::Forest()
{
	m_rootNode = new osg::Group;

	//���������������� ������
	InitBranches();

	//���������������� ����� ����
	InitFronds();
}

Forest::~Forest()
{

}

void Forest::InitBranches()
{
	//���������������� ������

	//���������������� �����
	osg::ref_ptr< BranchXML > branch = new BranchXML;

	for ( int i = 0 ; i < 20 ; ++i )
		for ( int j = 0 ; j < 20 ; ++j )
		{
			//������� ����, ���������� �����
			osg::ref_ptr< osg::Group > tree = new osg::Group;
			
			osg::StateSet *ss = tree->getOrCreateStateSet();

			//�������� ��������� ������ � ����
			tree->addChild( branch->getBranchGeode().get() );

			//�������� ���� � ���������� ������ � ��������� � ����� ���
			m_rootNode->addChild( tree.get() );

			//������ ��������� ����� uniform
			SetPos( ss , i * 100.0 , j * 100.0 );
		}
}

void Forest::InitFronds()
{
	//���������������� ����� ����
	
	//���������������� �����
	osg::ref_ptr< FrondsXML > fronds = new FrondsXML;

	for ( int i = 0 ; i < 20 ; ++i )
		for ( int j = 0 ; j < 20 ; ++j )
		{
			//������� ����, ���������� �����
			osg::ref_ptr< osg::Group > tree = new osg::Group;

			osg::StateSet *ss = tree->getOrCreateStateSet();

			//�������� ��������� ������ � ����
			tree->addChild( fronds->getFrondsGeode().get() );

			//�������� ���� � ���������� ������ � ��������� � ����� ���
			m_rootNode->addChild( tree.get() );

			//������ ��������� ����� uniform
			SetPos( ss , i * 100.0 , j * 100.0 );
		}
}

void Forest::SetPos( osg::StateSet *ss , float i , float j )
{
	//������ ��������� ����� uniform

	osg::ref_ptr< osg::Uniform > posOffset = new osg::Uniform( "posOffset" , osg::Vec3( j , i , 0.0 ) );
	ss->addUniform( posOffset.get() );
}
