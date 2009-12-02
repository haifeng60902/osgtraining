#ifndef _XML_BRANCH_NAMES_H_
#define _XML_BRANCH_NAMES_H_

#include <string>

struct xmlBranchNames
{
	xmlBranchNames() : m_sBranch( "branch" )
		, m_sTexture( "texture" )
		, m_sLODs( "LODs" )
	{};

	std::string m_sBranch;
	std::string m_sTexture;
	std::string m_sLODs;
};

#endif	//_XML_BRANCH_NAMES_H_