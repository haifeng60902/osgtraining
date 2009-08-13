#include "dataRGB.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <string>
#include <map>

std::map< dataRGB , int > res;
std::map< dataRGB , int > resNom;

//преобразовать цвет базовой текстуры в новый цвет
dataRGB ProcessPoint( const dataRGB &_rgb );

//преобразовать цвет в имя файла
std::string rgb2FileName( const dataRGB &_rgb );

//вставка изображения в нужное место
void PutImageInProperPlace( const std::string &_file , int ind , unsigned char *_data );

int main()
{
	// Load the texture image
	osg::ref_ptr< osg::Image > imageR = osgDB::readImageFile( "landcover9.bmp" );

	unsigned char *data = imageR->data();

	//получить размер текстуры
	int t = imageR->t();
	int s = imageR->s();
	int byte = imageR->getPixelSizeInBits() / 8;

	//заполнение map, для определения количества исполльзуемых текстур
	for ( int y = 0 ; y < t ; ++y )
		for ( int x = 0 ; x < s ; ++x )
		{
			dataRGB pix;
			pix.m_ucR = data[ y * s * byte + x * byte ];
			pix.m_ucG = data[ y * s * byte + x * byte + 1 ];
			pix.m_ucB = data[ y * s * byte + x * byte + 2 ];

			res[ pix ]++;
		}	

	//заполнение вспомогательного map для удобного нахождения индекса цвета
	std::map< dataRGB , int >::iterator it = res.begin();
	int i = 0;
	while( it != res.end() )
	{
		resNom[ it->first ] = i;
		++it;
		++i;
	}

//////////////////////////////////////////////////////////////////////////
	osg::ref_ptr< osg::Image > imageW = new osg::Image;

	imageW->allocateImage( s, t, 1, GL_RGB, GL_UNSIGNED_BYTE); 
	{
		unsigned char *dataW = imageW->data();

		//получить размер текстуры
		int t = imageW->t();
		int s = imageW->s();
		int byte = imageW->getPixelSizeInBits() / 8;

		for ( int y = 0 ; y < t ; ++y )
			for ( int x = 0 ; x < s ; ++x )
			{
				//извлечь цвет пикселя из базовой текстуры
				dataRGB pix;
				pix.m_ucR = data[ y * s * byte + x * byte ];
				pix.m_ucG = data[ y * s * byte + x * byte + 1 ];
				pix.m_ucB = data[ y * s * byte + x * byte + 2 ];

				//преобразовать цвет базовой текстуры в новый цвет
				dataRGB newPix = ProcessPoint( pix );

				//записать преобразованный цвет
				dataW[ y * s * byte + x * byte ] = newPix.m_ucR;
				dataW[ y * s * byte + x * byte + 1 ] = newPix.m_ucG;
				dataW[ y * s * byte + x * byte + 2 ] = newPix.m_ucB;	
			}

	}

	osgDB::writeImageFile( *imageW , "out.bmp" );

//////////////////////////////////////////////////////////////////////////
	//формирование составной текстуры

	osg::ref_ptr< osg::Image > imageBig = new osg::Image;
	imageBig->allocateImage( 4096, 4096, 1, GL_RGB, GL_UNSIGNED_BYTE);
	unsigned char *_dataBig = imageBig->data();

	//заполнение вспомогательного map для удобного нахождения индекса цвета
	std::map< dataRGB , int >::iterator itN = resNom.begin();
	while( itN != resNom.end() )
	{
		dataRGB rgb = itN->first;
		int ind = itN->second;

		//преобразовать цвет в имя файла
		std::string file = rgb2FileName( rgb );

		//вставка изображения в нужное место
		PutImageInProperPlace( file , ind , _dataBig );

		++itN;
	}

	osgDB::writeImageFile( *imageBig , "big.bmp" );
}

dataRGB ProcessPoint( const dataRGB &_rgb )
{
	//преобразовать цвет базовой текстуры в новый цвет
	dataRGB resRGB;

	int ind = resNom[ _rgb ];
	resRGB.m_ucR = ind % 16;
	resRGB.m_ucG = ind / 16;

	return resRGB;
}

std::string rgb2FileName( const dataRGB &_rgb )
{
	//преобразовать цвет в имя файла

	//таблица преобразования числа в имя файла
	std::map< int , std::string > m_ConvT;

	//заполнение таблицы преобразования файлов
	m_ConvT[ 0 ] = "Bs";	
	m_ConvT[ 21 ] = "Bt";
	m_ConvT[ 42 ] = "Ct";
	m_ConvT[ 63 ] = "D_";
	m_ConvT[ 84 ] = "Fd";
	m_ConvT[ 105 ] = "Ff";
	m_ConvT[ 126 ] = "Fr";
	m_ConvT[ 147 ] = "Gr";
	m_ConvT[ 168 ] = "Pl";
	m_ConvT[ 189 ] = "Rk";
	m_ConvT[ 210 ] = "Sn";
	m_ConvT[ 231 ] = "Vl";

	m_ConvT[ 1 ] = "_0";
	m_ConvT[ 2 ] = "_1";
	m_ConvT[ 3 ] = "_2";
	m_ConvT[ 4 ] = "_3";
	m_ConvT[ 5 ] = "_4";
	m_ConvT[ 6 ] = "_5";
	m_ConvT[ 7 ] = "_6";
	m_ConvT[ 8 ] = "_7";
	m_ConvT[ 9 ] = "_8";
	m_ConvT[ 10 ] = "_9";
	m_ConvT[ 11 ] = "_a";
	m_ConvT[ 12 ] = "_b";
	m_ConvT[ 13 ] = "_c";
	m_ConvT[ 14 ] = "_d";
	m_ConvT[ 15 ] = "_e";
	m_ConvT[ 16 ] = "_f";

	m_ConvT[ 17 ] = "_a_1";
	m_ConvT[ 18 ] = "_b_1";
	m_ConvT[ 19 ] = "_e_1";
	m_ConvT[ 20 ] = "_f_1";

	std::string file_name = m_ConvT[ _rgb.m_ucR ] + m_ConvT[ _rgb.m_ucG ];

	int ost = _rgb.m_ucB % 21;

	if ( ost )
	{
		int cel = _rgb.m_ucB / 21;
		file_name = file_name + m_ConvT[ cel * 21 ] + m_ConvT[ ost ];
	}
	else
		file_name += m_ConvT[ _rgb.m_ucB ];

	file_name += ".bmp";

	return file_name;
}

void PutImageInProperPlace( const std::string &_file , int ind , unsigned char *_data )
{
	//вставка изображения в нужное место
	std::string path = "E:/Share/wb/images/" + _file;
	osg::ref_ptr< osg::Image > image = osgDB::readImageFile( path );

	unsigned char *data = image->data();

	//получить размер текстуры
	int t = image->t();
	int s = image->s();
	int byte = image->getPixelSizeInBits() / 8;

	//получение индексов
	int indX = ind % 16;
	int indY = ind / 16;

	for ( int y = 0 ; y < t ; ++y )
		for ( int x = 0 ; x < s ; ++x )
		{
			//прочитать данные из очередного пикселя
			dataRGB pix;
			pix.m_ucR = data[ y * s * byte + x * byte ];
			pix.m_ucG = data[ y * s * byte + x * byte + 1 ];
			pix.m_ucB = data[ y * s * byte + x * byte + 2 ];

			//передать их в большую текстуру
			_data[ ( indY * 256 + y ) * 4096 * 3 + indX * 256 * 3 + x * 3 ] = pix.m_ucR;
			_data[ ( indY * 256 + y ) * 4096 * 3 + indX * 256 * 3 + x * 3 + 1 ] = pix.m_ucG;
			_data[ ( indY * 256 + y ) * 4096 * 3 + indX * 256 * 3 + x * 3 + 2 ] = pix.m_ucB;
		}	
}