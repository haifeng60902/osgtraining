#include "DynamicTextureCallback.h"

#include <iostream>

DynamicTextureCallback::DynamicTextureCallback( osg::ref_ptr<osg::Image> image )
{
	image0 = image;
}

DynamicTextureCallback::~DynamicTextureCallback()
{

}

void DynamicTextureCallback::operator()( osg::Node* node, osg::NodeVisitor* nv )
{
	unsigned char *data = image0->data();

	//получить размер текстуры
	int t = image0->t();
	int s = image0->s();
	int byte = image0->getPixelSizeInBits() / 8;

	for ( int i = 0; i < image0->t() ; ++i )
		for ( int j = 0 ; j < image0->s() * byte ; ++j )
			data[ i * image0->t() * byte + j ] = GetRand();

	image0->dirty();
}

unsigned char DynamicTextureCallback::GetRand()
{
	return (float)rand() / (float)RAND_MAX * 255;
}