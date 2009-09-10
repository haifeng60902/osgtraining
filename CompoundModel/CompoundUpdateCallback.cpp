#include "CompoundUpdateCallback.h"

#include <iostream>

CompoundUpdateCallback::CompoundUpdateCallback()
{

}

CompoundUpdateCallback::~CompoundUpdateCallback()
{

}

void CompoundUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);

	//обновить картинку
	UpdateImage();
}

void CompoundUpdateCallback::UpdateImage()
{
	//обновить картинку
	unsigned char *data = m_Image->data();

	//получить размер текстуры
	int t = m_Image->t();
	int s = m_Image->s();
	int byte = m_Image->getPixelSizeInBits() / 8;

	int count = 0;

	for ( int i = 0; i < t ; ++i )
		for ( int j = 0 ; j < s ; ++j )
		{	
			float *mR = (float*)( &data[ i * t * byte + j * byte ] );
			float *mG = (float*)( &data[ i * t * byte + j * byte + 4 ] );
			float *mB = (float*)( &data[ i * t * byte + j * byte + 8 ] );
			float *mA = (float*)( &data[ i * t * byte + j * byte + 12 ] );

		
			( *mR ) = (float)j / (float)s;
			( *mG ) = (float)i / (float)s;
			( *mB ) = GetFloatRand();
			( *mA ) = GetFloatRand();

			++count;
		}

	m_Image->dirty();
}

float CompoundUpdateCallback::GetFloatRand()
{
	return (float)rand() / (float)RAND_MAX;
}