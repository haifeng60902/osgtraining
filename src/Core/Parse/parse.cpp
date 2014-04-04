#include "Core\Parse\parse.h"

void Parse::Substr(const std::string& msg, tVecStr* vStr)
{
	std::string::size_type pos=0;
	while (pos != std::string::npos)
	{
		std::string::size_type pos1=msg.find("|",pos);
		if (pos1 != std::string::npos)
		{
			std::string sStr=msg.substr(pos,pos1-pos);
			vStr->push_back(sStr);
			++pos1;
		}
		pos=pos1;
	}
}

int Parse::GetInt(const std::string& msg, const std::string& param)
{
	int iRes=0;
	std::string::size_type pos=msg.find(param.c_str(),0);
	if (pos!=std::string::npos)
	{
		std::string::size_type pos1=msg.find(",", pos);
		if (pos1==std::string::npos)
			pos1=msg.size();
		std::string sVal=msg.substr(pos+param.size(),pos1-pos-param.size());
		iRes=atoi(sVal.c_str());
	}
	return iRes;
}

std::string Parse::GetStr(const std::string& msg, const std::string& param)
{
	std::string sRes;
	std::string::size_type pos=msg.find(param.c_str(),0);
	if (pos!=std::string::npos)
	{
		std::string::size_type pos1=msg.find(",", pos);
		if (pos1==std::string::npos)
			pos1=msg.size();
		sRes=msg.substr(pos+param.size(),pos1-pos-param.size());
	}
	return sRes;
}

double Parse::GetDouble(const std::string& msg, const std::string& param)
{
	double dRes=0.0f;
	std::string::size_type pos=msg.find(param.c_str(),0);
	if (pos!=std::string::npos)
	{
		std::string::size_type pos1=msg.find(",", pos);
		if (pos1==std::string::npos)
			pos1=msg.size();
		std::string sVal=msg.substr(pos+param.size(),pos1-pos-param.size());
		dRes=atof(sVal.c_str());
	}
	return dRes;
}

bool Parse::BoolDetect(std::string sBool)
{
	bool bRes=false;
	if (sBool.compare("true")==0)
		bRes=true;

	return bRes;
}