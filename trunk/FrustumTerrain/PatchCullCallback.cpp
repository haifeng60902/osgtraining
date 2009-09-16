#include "PatchCullCallback.h"

#include "FrustumSingleton.h"

#include <iostream>

PatchCullCallback::PatchCullCallback()
{

}

PatchCullCallback::~PatchCullCallback()
{

}

void PatchCullCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	// first update subgraph to make sure objects are all moved into position
	traverse(node,nv);

	//сформировать массив данных о видимых патчах
	m_VisiblePatchArray.Update();

	//обновить картинку
	UpdateImage();
}

void PatchCullCallback::UpdateImage()
{
	//обновить картинку
	unsigned char *data = m_Image->data();

	//получить размер текстуры
	int t = m_Image->t();
	int s = m_Image->s();
	int byte = m_Image->getPixelSizeInBits() / 8;

	//вернуть ссылку на массив видимых патчей
	const std::vector< dataPatch > &data_vis = m_VisiblePatchArray.GetVisibleArray();

	//if ( !data_vis.empty() )
	//	std::cout << data_vis.size() << " ";

	int count = 0;

	for ( int i = 0; i < t ; ++i )
		for ( int j = 0 ; j < s ; ++j )
		{	
			float *mR = (float*)( &data[ i * t * byte + j * byte ] );
			float *mG = (float*)( &data[ i * t * byte + j * byte + 4 ] );
			float *mB = (float*)( &data[ i * t * byte + j * byte + 8 ] );
			float *mA = (float*)( &data[ i * t * byte + j * byte + 12 ] );

			if ( count < data_vis.size() )
			{
				( *mR ) = data_vis[ count ].m_iX / 262144.0;
				( *mG ) = data_vis[ count ].m_iY / 262144.0;
				( *mB ) = 1.0f;
				( *mA ) = 1.0f;
			}
			else
			{
				//данные закончились
				( *mR ) = 0.0f;
				( *mG ) = 0.0f;
				( *mB ) = 0.0f;
				( *mA ) = 0.0f;
			}

			++count;
		}

	m_Image->dirty();
}

float PatchCullCallback::GetFloatRand()
{
	return (float)rand() / (float)RAND_MAX;
}