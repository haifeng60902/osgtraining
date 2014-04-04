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
	case enPools:
		decodePools(msg);
		break;
	case enCoin:
		decodeCoin(msg);
		break;
	case enDevs:
		decodeDevs(msg);
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

	if (vStr.size()>1)
	{
		binSummary s;
		s.tTime=GetInt(vStr[0],"When=");
		s.sDesc=GetStr(vStr[0],"Description=");
		s.iElapsed=GetInt(vStr[1],"Elapsed=");
		s.fMHSav=GetDouble(vStr[1],"MHS av=");
		s.fMHS5s=GetDouble(vStr[1],"MHS 5s=");
		s.iFoundBlocks=GetInt(vStr[1],"Found Blocks=");
		s.iGetworks=GetInt(vStr[1],"Getworks=");
		s.iAccepted=GetInt(vStr[1],"Accepted=");
		s.iRejected=GetInt(vStr[1],"Rejected=");
		s.iHardwareErrors=GetInt(vStr[1],"Hardware Errors=");
		s.fUtility=GetDouble(vStr[1],"Utility=");
		s.iDiscarded=GetInt(vStr[1],"Discarded=");
		s.iStale=GetInt(vStr[1],"Stale=");
		s.iGetFailures=GetInt(vStr[1],"Get Failures=");
		s.iLocalWork=GetInt(vStr[1],"Local Work=");
		s.iRemoteFailures=GetInt(vStr[1],"Remote Failures=");
		s.iNetworkBlocks=GetInt(vStr[1],"Network Blocks=");
		s.fTotalMH=GetDouble(vStr[1],"Total MH=");
		s.fWorkUtility=GetDouble(vStr[1],"Work Utility=");
		s.fDifficultyAccepted=GetDouble(vStr[1],"Difficulty Accepted=");
		s.fDifficultyRejected=GetDouble(vStr[1],"Difficulty Rejected=");
		s.fDifficultyStale=GetDouble(vStr[1],"Difficulty Stale=");
		s.iBestShare=GetInt(vStr[1],"Best Share=");
		s.fDeviceHardware=GetDouble(vStr[1],"Device Hardware%=");
		s.fDeviceRejected=GetDouble(vStr[1],"Device Rejected%=");
		s.fPoolRejected=GetDouble(vStr[1],"Pool Rejected%=");
		s.fPoolStale=GetDouble(vStr[1],"Pool Stale%=");

		vSummary.push_back(s);
	}
}

void decodeFeedback::decodePools(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	parseSubstr(msg, &vStr);

	if (!vStr.empty())
	{
		binPools ps;
		ps.tTime=GetInt(vStr[0],"When=");
		ps.sDesc=GetStr(vStr[0],"Description=");
		if (vStr.size()>1)
			for(int i=1;i<vStr.size();++i)
			{
				binPool p;
				p.iPOOL=GetInt(vStr[i],"POOL=");
				p.sURL=GetStr(vStr[i],"URL=");
				p.sStatus=GetStr(vStr[i],"Status=");
				p.iPriority=GetInt(vStr[i],"Priority=");
				p.iQuota=GetInt(vStr[i],"Quota=");
				p.sLongPoll=GetStr(vStr[i],"Long Poll=");
				p.iGetworks=GetInt(vStr[i],"Getworks=");
				p.iAccepted=GetInt(vStr[i],"Accepted=");
				p.iRejected=GetInt(vStr[i],"Rejected=");
				p.iWorks=GetInt(vStr[i],"Works=");
				p.iDiscarded=GetInt(vStr[i],"Discarded=");
				p.iStale=GetInt(vStr[i],"Stale=");
				p.iGetFailures=GetInt(vStr[i],"Get Failures=");
				p.iRemoteFailures=GetInt(vStr[i],"Remote Failures=");
				p.sUser=GetStr(vStr[i],"User=");
				p.tLastShareTime=GetInt(vStr[i],"Last Share Time=");
				p.iDiff1Shares=GetInt(vStr[i],"Diff1 Shares=");
				p.sProxyType=GetStr(vStr[i],"Proxy Type=");
				p.sProxy=GetStr(vStr[i],"Proxy=");
				p.fDifficultyAccepted=GetDouble(vStr[i],"Difficulty Accepted=");
				p.fDifficultyRejected=GetDouble(vStr[i],"Difficulty Rejected=");
				p.fDifficultyStale=GetDouble(vStr[i],"Difficulty Stale=");
				p.fLastShareDifficulty=GetDouble(vStr[i],"Last Share Difficulty=");
				
				std::string sBool;
				sBool=GetStr(vStr[i],"Has Stratum=");
				p.bHasStratum=BoolDetect(sBool);

				sBool=GetStr(vStr[i],"Stratum Active=");
				p.bStratumActive=p.bHasStratum=BoolDetect(sBool);

				p.sStratumURL=GetStr(vStr[i],"Stratum URL=");

				sBool=GetStr(vStr[i],"Has GBT=");
				p.bHasGBT=BoolDetect(sBool);

				p.iBestShare=GetInt(vStr[i],"Best Share=");
				p.fPoolRejected=GetDouble(vStr[i],"Pool Rejected%=");
				p.fPoolStale=GetDouble(vStr[i],"Pool Stale%=");

				ps.vPool.push_back(p);
			}
		vPools.push_back(ps);
	}
}

void decodeFeedback::decodeCoin(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	parseSubstr(msg, &vStr);

	if (vStr.size()>1)
	{
		binCoin c;

		c.tTime=GetInt(vStr[0],"When=");
		c.sDesc=GetStr(vStr[0],"Description=");
		c.sHashMethod=GetStr(vStr[1],"Hash Method=");
		c.dCurrentBlockTime=GetDouble(vStr[1],"Current Block Time=");
		c.sCurrentBlockHash=GetStr(vStr[1],"Current Block Hash=");

		std::string sBool;
		sBool=GetStr(vStr[1],"LP=");
		c.bLP=BoolDetect(sBool);
		c.fNetworkDifficulty=GetDouble(vStr[1],"Network Difficulty=");

		vCoin.push_back(c);
	}
}

void decodeFeedback::decodeDevs(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	parseSubstr(msg, &vStr);

	if (vStr.size()>1)
	{
		binDevs d;
		d.tTime=GetInt(vStr[0],"When=");
		d.sDesc=GetStr(vStr[0],"Description=");
		for (int i=1;i<vStr.size();++i)
		{
			binGpu g;

			g.iGPU=GetInt(vStr[i],"GPU=");
			g.sEnabled=GetStr(vStr[i],"Enabled=");
			g.sStatus=GetStr(vStr[i],"Status=");
			g.fTemperature=GetDouble(vStr[i],"Temperature=");
			g.iFanSpeed=GetInt(vStr[i],"Fan Speed=");
			g.iFanPercent=GetInt(vStr[i],"Fan Percent=");
			g.iGPUClock=GetInt(vStr[i],"GPU Clock=");
			g.iMemoryClock=GetInt(vStr[i],"Memory Clock=");
			g.fGPUVoltage=GetDouble(vStr[i],"GPU Voltage=");
			g.iGPUActivity=GetInt(vStr[i],"GPU Activity=");
			g.iPowertune=GetInt(vStr[i],"Powertune=");
			g.fMHSav=GetDouble(vStr[i],"MHS av=");
			g.fMHS5s=GetDouble(vStr[i],"MHS 5s=");
			g.iAccepted=GetInt(vStr[i],"Accepted=");
			g.iRejected=GetInt(vStr[i],"Rejected=");
			g.iHardwareErrors=GetInt(vStr[i],"Hardware Errors=");
			g.fUtility=GetDouble(vStr[i],"Utility=");
			g.iIntensity=GetInt(vStr[i],"Intensity=");
			g.tLastSharePool=GetInt(vStr[i],"Last Share Pool=");
			g.tLastShareTime=GetInt(vStr[i],"Last Share Time=");
			g.fTotalMH=GetDouble(vStr[i],"Total MH=");
			g.iDiff1Work=GetInt(vStr[i],"Diff1 Work=");
			g.fDifficultyAccepted=GetDouble(vStr[i],"Difficulty Accepted=");
			g.fDifficultyRejected=GetDouble(vStr[i],"Difficulty Rejected=");
			g.fLastShareDifficulty=GetDouble(vStr[i],"Last Share Difficulty=");
			g.tLastValidWork=GetInt(vStr[i],"Last Valid Work=");
			g.fDeviceHardware=GetDouble(vStr[i],"Device Hardware%=");
			g.fDeviceRejected=GetDouble(vStr[i],"Device Rejected%=");
			g.iDeviceElapsed=GetInt(vStr[i],"Device Elapsed=");

			d.vGpu.push_back(g);
		}

		vDevs.push_back(d);
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

double decodeFeedback::GetDouble(const std::string& msg, const std::string& param)
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

bool decodeFeedback::BoolDetect(std::string sBool)
{
	bool bRes=false;
	if (sBool.compare("true")==0)
		bRes=true;

	return bRes;
}