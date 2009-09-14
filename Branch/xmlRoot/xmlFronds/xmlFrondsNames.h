#ifndef _XML_FRONDS_NAMES_H_
#define _XML_FRONDS_NAMES_H_

#include <string>

struct xmlFrondsNames
{
	xmlFrondsNames() : m_sFronds( "fronds" )
		, m_sAlfaTest( "alfa" )
		, m_sTextures( "textures" )
		, m_sLODs( "LODs" )
		, m_sLOD( "LOD" ) 
		, m_sTexture( "texture" )
		, m_sVertexs( "vertexs" )
		, m_sNum( "num" )
		, m_sPoint( "point" )
		, m_sX( "x" )
		, m_sY( "y" )
		, m_sZ( "z" )

		, m_snX( "nx" )
		, m_snY( "ny" )
		, m_snZ( "nz" )

		, m_sS( "s" )
		, m_sT( "t" )
		, m_sP( "p" )
		, m_sQ( "q" )

		, m_sStrips( "strips" )
		, m_sStrip( "strip" )
		, m_sInd( "ind" )
		, m_sVal( "val" )
	{};

	std::string m_sFronds;
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
	
	std::string m_sS;
	std::string m_sT;
	std::string m_sP;
	std::string m_sQ;

	std::string m_sStrips;
	std::string m_sStrip;
	std::string m_sInd;
	std::string m_sVal;
};

static xmlFrondsNames m_FrondsNames;

#endif	//_XML_FRONDS_NAMES_H_