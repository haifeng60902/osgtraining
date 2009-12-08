#ifndef _XML_LEAF_NAMES_H_
#define _XML_LEAF_NAMES_H_

#include <string>

struct xmlLeafNames
{
	xmlLeafNames() : m_sLeaf( "leaf" )
		, m_sAlfaTest( "alfa" )
		, m_sTextures( "textures" )
		, m_sTexture( "texture" )
		, m_sLODs( "LODs" )
		, m_sLOD( "LOD" )
		, m_sVertexs( "vertexs" )
		, m_sNum( "num" )
		, m_sPoint( "point" )
		, m_sX( "x" )
		, m_sY( "y" )
		, m_sZ( "z" )

		, m_snX( "nx" )
		, m_snY( "ny" )
		, m_snZ( "nz" )

		, m_sS0( "s0" )
		, m_sT0( "t0" )
		, m_sP0( "p0" )
		, m_sQ0( "q0" )
		, m_sS1( "s1" )
		, m_sT1( "t1" )
		, m_sP1( "p1" )
		, m_sVal( "val" )
	{};

	std::string m_sLeaf;
	std::string m_sAlfaTest;
	std::string m_sTextures;
	std::string m_sTexture;
	std::string m_sLODs;
	std::string m_sLOD;
	std::string m_sVertexs;
	std::string m_sNum;
	std::string m_sPoint;

	std::string m_sX;
	std::string m_sY;
	std::string m_sZ;

	std::string m_snX;
	std::string m_snY;
	std::string m_snZ;

	std::string m_sS0;
	std::string m_sT0;
	std::string m_sP0;
	std::string m_sQ0;
	std::string m_sS1;
	std::string m_sT1;
	std::string m_sP1;

	std::string m_sVal;
};

static xmlLeafNames m_LeafNames;

#endif	//_XML_LEAF_NAMES_H_