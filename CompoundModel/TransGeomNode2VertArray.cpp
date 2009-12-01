#include "TransGeomNode2VertArray.h"

#include <osg/Geode>

#include <iostream>

TransGeomNode2VertArray::TransGeomNode2VertArray() : osg::NodeVisitor( osg::NodeVisitor::TRAVERSE_ALL_CHILDREN )
	, m_V3( NULL)
	, m_iPrevInd0( -1 )
	, m_iPrevInd1( -1 )
	, m_iPrevInd2( -1 )
{

}

TransGeomNode2VertArray::~TransGeomNode2VertArray()
{

}

void TransGeomNode2VertArray::apply( osg::Node& node )
{
	//метод вызывается для каждого узла в сцене

	//приводим указатель к типу Geode
	
	osg::Geode* mtGeode = dynamic_cast< osg::Geode* >( &node );

	if ( mtGeode )
	{
		//получить количество Drawable узлов
		unsigned int numDr = mtGeode->getNumDrawables();

		std::cout << "osg::Geode: " << mtGeode->getName() << "\n";

		//перебрать все дочерние Geometry узлы
		for ( unsigned int i = 0; i < numDr; ++i )
		{
			//получить Geometry узел
			const osg::Geometry *mtDrawable = dynamic_cast< osg::Geometry* >( mtGeode->getDrawable( i ) );

			if ( mtDrawable )
			{
				//извлечь имя узла
				std::string _name( mtDrawable->getName() );

				std::cout << "osg::Geometry: " << _name << "\n";

				//Обработать Drawable узел
				ProcessDrawableNode( mtDrawable );
			}
			else
				std::cout << "WARNING: The " << i << " geometry is not drawable!\n";
		}
		std::cout << "\n";
	}

	//продолжаем обход узлов сцены
	traverse( node );
}

void TransGeomNode2VertArray::ProcessDrawableNode( const osg::Geometry *mtDrawable )
{
//Обработать Drawable узел

	//получить указатель на массив вершин узла
	const osg::Array *v = mtDrawable->getVertexArray();

	//получить указатель на массив нормалей узла
	const osg::Array *n = mtDrawable->getNormalArray();

	//получить указатель на массив цветов узла
	const osg::Array *c = mtDrawable->getColorArray();

	//получить указатель на массив текстурных координат 0 узла
	const osg::Array *tc0 = mtDrawable->getTexCoordArray(0);

	//получить указатель на массив текстурных координат 0 узла
	const osg::Array *tc1 = mtDrawable->getTexCoordArray(1);

	//привести указатель к типу vec3f
	m_V3 = dynamic_cast< const osg::Vec3Array* >( v );

	//привести указатель к типу vec3f
	m_N3 = dynamic_cast< const osg::Vec3Array* >( n );

	osg::Geometry::AttributeBinding attr = mtDrawable->getNormalBinding();

	//привести указатель к типу vec4f
	const osg::Vec4Array *c4 = dynamic_cast< const osg::Vec4Array* >( c );

	//привести указатель к типу vec2f
	m_TC0 = dynamic_cast< const osg::Vec2Array* >( tc0 );

	//привести указатель к типу vec2f
	const osg::Vec2Array *tc21 = dynamic_cast< const osg::Vec2Array* >( tc1 );

	if ( m_V3 )
	{
		//получить количество наборов примитивов
		int numPrSet = mtDrawable->getNumPrimitiveSets();
		for ( int i = 0; i < numPrSet; ++i )
		{
			//извлечь набор примитивов
			const osg::PrimitiveSet *pr_set = mtDrawable->getPrimitiveSet( i );

			//заполнить вектор вершин
			FillVertexData( m_V3 , m_N3 , pr_set );
		}
	}
	else
		std::cout << "WARNING: The drawable nod's vertex data is not osg::Vec3Array!\n";
}

void TransGeomNode2VertArray::FillVertexData( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set )
{
	//заполнить вектор вершин

	//определить тип примитивов и режим
	osg::PrimitiveSet::Type tp = pr_set->getType();

	switch ( tp )
	{
	case osg::PrimitiveSet::Type::PrimitiveType :
		std::cout << "WARNING: Unknown type - PrimitiveType\n";
		break;
	case osg::PrimitiveSet::Type::DrawArraysPrimitiveType :
		//обработать массив, содержащий вершины типа DrawArraysPrimitiveType
		ProcessPrimitiveType( v3 , n3 , pr_set );
		break;
	case osg::PrimitiveSet::Type::DrawArrayLengthsPrimitiveType :
		std::cout << "WARNING: Unknown type - DrawArrayLengthsPrimitiveType\n";
		break;
	case osg::PrimitiveSet::Type::DrawElementsUBytePrimitiveType :
		//обработать массив, содержащий индексы на вершины типа DrawElementsUBytePrimitiveType
		ProcessUByteIndex( v3 , n3 , pr_set );
		break;
	case osg::PrimitiveSet::Type::DrawElementsUShortPrimitiveType :
		//обработать массив, содержащий индексы на вершины типа DrawElementsUShortPrimitiveType
		ProcessUShortIndex( v3 , n3 , pr_set );
		break;
	case osg::PrimitiveSet::Type::DrawElementsUIntPrimitiveType :
		//обработать массив, содержащий индексы на вершины типа DrawElementsUIntPrimitiveType
		ProcessUIntIndex( v3 , n3 , pr_set );
		break;
	}
}

void TransGeomNode2VertArray::ProcessPrimitiveType( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set )
{
	//обработать массив, содержащий вершины типа DrawArraysPrimitiveType
	const osg::DrawArrays *da = dynamic_cast< const osg::DrawArrays * >( pr_set );

	if ( da )
	{
		int numInd = da->getNumIndices();
		for ( int i = 0; i < da->getNumIndices(); ++i )
		{
			int ind = da->index( i );

			//получить режим формирования примитивов
			GLenum mode = da->getMode();

			//обработать данные узла
			ProcessVertexNode( v3 , n3 , i , ind , mode );
		}
	}
	else
		std::cout << "WARNING: Dynamic cast operation error for DrawArrays type\n";
}

void TransGeomNode2VertArray::ProcessUByteIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set )
{
	//обработать массив, содержащий индексы на вершины типа DrawElementsUBytePrimitiveType
	const osg::DrawElementsUByte *de_ub = dynamic_cast< const osg::DrawElementsUByte * >( pr_set );

	if ( de_ub )
	{
		for ( int i = 0; i < de_ub->size(); ++i )
		{
			int ind = (*de_ub)[ i ];

			//получить режим формирования примитивов
			GLenum mode = de_ub->getMode();

			//обработать данные узла
			ProcessVertexNode( v3 , n3 , i , ind , mode );
		}
	}
	else
		std::cout << "WARNING: Dynamic cast operation error for DrawElementsUByte type\n";
}

void TransGeomNode2VertArray::ProcessUShortIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set )
{
	//обработать массив, содержащий индексы на вершины типа DrawElementsUShortPrimitiveType
	const osg::DrawElementsUShort *de_us = dynamic_cast< const osg::DrawElementsUShort * >( pr_set );

	if ( de_us )
	{
		for ( int i = 0; i < de_us->size(); ++i )
		{
			int ind = (*de_us)[ i ];
			
			//получить режим формирования примитивов
			GLenum mode = de_us->getMode();

			//обработать данные узла
			ProcessVertexNode( v3 , n3 , i , ind , mode );
		}
	}
	else
		std::cout << "WARNING: Dynamic cast operation error for DrawElementsUShort type\n";
}

void TransGeomNode2VertArray::ProcessUIntIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , const osg::PrimitiveSet *pr_set )
{
	//обработать массив, содержащий индексы на вершины типа DrawElementsUBytePrimitiveType
	const osg::DrawElementsUInt *de_ui = dynamic_cast< const osg::DrawElementsUInt * >( pr_set );

	if ( de_ui )
	{
		for ( int i = 0; i < de_ui->size(); ++i )
		{
			int ind = (*de_ui)[ i ];

			//получить режим формирования примитивов
			GLenum mode = de_ui->getMode();

			//обработать данные узла
			ProcessVertexNode( v3 , n3 , i , ind , mode );
		}
	}
	else
		std::cout << "WARNING: Dynamic cast operation error for DrawElementsUInt type\n";
}

void TransGeomNode2VertArray::ProcessVertexNode( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind , GLenum mode )
{
	//обработать данные узла
	switch ( mode )
	{
	case GL_POINTS:
		std::cout << "WARNING: Unknown mode - GL_POINTS\n";
		break;
	case GL_LINES:
		std::cout << "WARNING: Unknown mode - GL_LINES\n";
		break;
	case GL_LINE_LOOP:
		std::cout << "WARNING: Unknown mode - GL_LINE_LOOP\n";
		break;
	case GL_LINE_STRIP:
		std::cout << "WARNING: Unknown mode - GL_LINE_STRIP\n";
		break;
	case GL_TRIANGLES:
		//обработать режим GL_TRIANGLES
		ProcessTriangles( v3 , n3 , nom , ind );
		break;
	case GL_TRIANGLE_STRIP:
		//обработать режим GL_TRIANGLE_STRIP
		ProcessTriangleStrip( v3 , n3 , nom , ind );
		break;
	case GL_TRIANGLE_FAN:
		//обработать режим GL_TRIANGLE_FAN
		ProcessTriangleFun( v3 , n3 , nom , ind );
		break;
	case GL_QUADS:
		std::cout << "WARNING: Unknown mode - GL_QUADS\n";
		break;
	case GL_QUAD_STRIP:
		std::cout << "WARNING: Unknown mode - GL_QUAD_STRIP\n";
		break;
	case GL_POLYGON:
		std::cout << "WARNING: Unknown mode - GL_POLYGON\n";
		break;
	}
}

void TransGeomNode2VertArray::ProcessTriangles( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind )
{
//обработать режим GL_TRIANGLES

	SaveVertex( v3 , n3 , ind );
/*
	osg::Vec3d _ver( (*v3)[ ind ][ 0 ] , (*v3)[ ind ][ 1 ] , (*v3)[ ind ][ 2 ]);

	_ver = _ver * m_Matrix;

	osg::Vec3d _nor( (*n3)[ ind ][ 0 ] , (*n3)[ ind ][ 1 ] , (*n3)[ ind ][ 2 ]);

	osg::Matrix inv	= osg::Matrix::inverse( m_Matrix );

	osg::Matrix trtr( inv( 0 , 0 ) , inv( 1 , 0 ) , inv( 2 , 0 ) , inv( 3 , 0 ) ,
		inv( 0 , 1 ) , inv( 1 , 1 ) , inv( 2 , 1 ) , inv( 3 , 1 ) ,
		inv( 0 , 2 ) , inv( 1 , 2 ) , inv( 2 , 2 ) , inv( 3 , 2 ) ,
		inv( 0 , 3 ) , inv( 1 , 3 ) , inv( 2 , 3 ) , inv( 3 , 3 ) );

	_nor = _nor * trtr;

	m_vVer.push_back( _ver.x() );
	m_vVer.push_back( _ver.y() );
	m_vVer.push_back( _ver.z() );
	*/
}

void TransGeomNode2VertArray::ProcessTriangleStrip( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind )
{
	//обработать режим GL_TRIANGLE_STRIP
	if ( nom < 3 )
		//запомнить вершину в формируемом массиве
		SaveVertex( v3 , n3 , ind );
	else
	{
		//находим остаток
		int iOst = nom % 2;

		//индекс нечетный
		if ( iOst )
			//обработать индексы для режима GL_TRIANGLE_STRIP
			ProcessIndex( v3 , n3 , m_iPrevInd2 , m_iPrevInd1 , ind );
		else
			//обработать индексы для режима GL_TRIANGLE_STRIP
			ProcessIndex( v3 , n3 , m_iPrevInd0 , m_iPrevInd2 , ind );
	}

	//сместить индексы
	OffsetPrevIndex( ind );
}

void TransGeomNode2VertArray::OffsetPrevIndex( int ind )
{
	//сместить индексы
	m_iPrevInd0 = m_iPrevInd1;
	m_iPrevInd1 = m_iPrevInd2;
	m_iPrevInd2 = ind;
}

void TransGeomNode2VertArray::SaveVertex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int ind )
{
	//запомнить вершину в формируемом массиве

	osg::Vec3d _ver( (*v3)[ ind ][ 0 ] , (*v3)[ ind ][ 1 ] , (*v3)[ ind ][ 2 ]);
	osg::Vec3d _nor( (*n3)[ ind ][ 0 ] , (*n3)[ ind ][ 1 ] , (*n3)[ ind ][ 2 ]);

	//_ver = _ver * m_Matrix;

	m_vVer.push_back( _ver.x() );
	m_vVer.push_back( _ver.y() );
	m_vVer.push_back( _ver.z() );

	m_vNor.push_back( _nor.x() );
	m_vNor.push_back( _nor.y() );
	m_vNor.push_back( _nor.z() );
}

void TransGeomNode2VertArray::ProcessIndex( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int ind0 , int ind1 , int ind2 )
{
	//обработать индексы для режима GL_TRIANGLE_STRIP

	//запомнить вершину в формируемом массиве
	SaveVertex( v3 , n3 , ind0 );

	//запомнить вершину в формируемом массиве
	SaveVertex( v3 , n3 , ind1 );

	//запомнить вершину в формируемом массиве
	SaveVertex( v3 , n3 , ind2 );
}

void TransGeomNode2VertArray::ProcessTriangleFun( const osg::Vec3Array *v3 , const osg::Vec3Array *n3 , int nom , int ind )
{
	//обработать режим GL_TRIANGLE_FAN
	if ( nom < 3 )
		//запомнить вершину в формируемом массиве
		SaveVertex( v3 , n3 , ind );
	else
		//обработать индексы для режима GL_TRIANGLE_FAN
		ProcessIndex( v3 , n3 , 0 , m_iPrevInd2 , ind );

	//сместить индексы
	OffsetPrevIndex( ind );
}

void TransGeomNode2VertArray::ComputeNormalMatrix()
{
	//вычислить матрицу для трансформации нормалей

	//нахождение обратной матрицы
	osg::Matrix inv	= osg::Matrix::inverse( m_Matrix );

	//транспонирование матрицы
	m_Matrix4Normal.set( inv( 0 , 0 ) , inv( 1 , 0 ) , inv( 2 , 0 ) , inv( 3 , 0 ) ,
		inv( 0 , 1 ) , inv( 1 , 1 ) , inv( 2 , 1 ) , inv( 3 , 1 ) ,
		inv( 0 , 2 ) , inv( 1 , 2 ) , inv( 2 , 2 ) , inv( 3 , 2 ) ,
		inv( 0 , 3 ) , inv( 1 , 3 ) , inv( 2 , 3 ) , inv( 3 , 3 ) );
}