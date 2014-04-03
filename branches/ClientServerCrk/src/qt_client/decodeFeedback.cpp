#include "decodeFeedback.h"

decodeFeedback::decodeFeedback()
{

}

decodeFeedback::~decodeFeedback()
{

}

void decodeFeedback::decode(eMinerMode mode, const std::string& msg)
{
	switch (mode)
	{
	case enSummary:
		decodeSummary(msg);
		break;
	default:
		break;
	}
}

void decodeFeedback::decodeSummary(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	parseSubstr(msg, &vStr);

	if (!vStr.empty())
	{
		binSummary s;
		s.tTime=GetInt(vStr[0],"When=");
		s.sDesc=GetStr(vStr[0],"Description=");
		s.iElapsed=GetInt(vStr[1],"Elapsed=");
		s.fMHSav=GetFloat(vStr[1],"MHS av=");
		s.fMHS5s=GetFloat(vStr[1],"MHS 5s=");
		s.iFoundBlocks=GetInt(vStr[1],"Found Blocks=");
		s.iGetworks=GetInt(vStr[1],"Getworks=");
		s.iAccepted=GetInt(vStr[1],"Accepted=");
		s.iRejected=GetInt(vStr[1],"Rejected=");
		s.iHardwareErrors=GetInt(vStr[1],"Hardware Errors=");
		s.fUtility=GetFloat(vStr[1],"Utility=");
		s.iDiscarded=GetInt(vStr[1],"Discarded=");
		s.iStale=GetInt(vStr[1],"Stale=");
		s.iGetFailures=GetInt(vStr[1],"Get Failures=");
		s.iLocalWork=GetInt(vStr[1],"Local Work=");
		s.iRemoteFailures=GetInt(vStr[1],"Remote Failures=");
		s.iNetworkBlocks=GetInt(vStr[1],"Network Blocks=");
		s.fTotalMH=GetFloat(vStr[1],"Total MH=");
		s.fWorkUtility=GetFloat(vStr[1],"Work Utility=");
		s.fDifficultyAccepted=GetFloat(vStr[1],"Difficulty Accepted=");
		s.fDifficultyRejected=GetFloat(vStr[1],"Difficulty Rejected=");
		s.fDifficultyStale=GetFloat(vStr[1],"Difficulty Stale=");
		s.iBestShare=GetInt(vStr[1],"Best Share=");
		s.fDeviceHardware=GetFloat(vStr[1],"Device Hardware%=");
		s.fDeviceRejected=GetFloat(vStr[1],"Device Rejected%=");
		s.fPoolRejected=GetFloat(vStr[1],"Pool Rejected%=");
		s.fPoolStale=GetFloat(vStr[1],"Pool Stale%=");

		vSummary.push_back(s);
	}
}

void decodeFeedback::parseSubstr(const std::string& msg, tVecStr* vStr)
{
	//helper func: parse str to some substr separated by "|" 
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

int decodeFeedback::GetInt(const std::string& msg, const std::string& param)
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

std::string decodeFeedback::GetStr(const std::string& msg, const std::string& param)
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

float decodeFeedback::GetFloat(const std::string& msg, const std::string& param)
{
	float fRes=0.0f;
	std::string::size_type pos=msg.find(param.c_str(),0);
	if (pos!=std::string::npos)
	{
		std::string::size_type pos1=msg.find(",", pos);
		if (pos1==std::string::npos)
			pos1=msg.size();
		std::string sVal=msg.substr(pos+param.size(),pos1-pos-param.size());
		fRes=atof(sVal.c_str());
	}
	return fRes;
}