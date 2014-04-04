#include "decodeFeedback.h"
#include "core/Parse/parse.h"

decodeFeedback::decodeFeedback()
{

}

decodeFeedback::~decodeFeedback()
{

}

void decodeFeedback::parse(eMinerMode mode, const std::string& msg)
{
	//decode string to binary data
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
	Parse::Substr(msg, &vStr);

	if (vStr.size()>1)
	{
		binSummary s;
		s.tTime=Parse::GetInt(vStr[0],"When=");
		s.sDesc=Parse::GetStr(vStr[0],"Description=");
		s.iElapsed=Parse::GetInt(vStr[1],"Elapsed=");
		s.fMHSav=Parse::GetDouble(vStr[1],"MHS av=");
		s.fMHS5s=Parse::GetDouble(vStr[1],"MHS 5s=");
		s.iFoundBlocks=Parse::GetInt(vStr[1],"Found Blocks=");
		s.iGetworks=Parse::GetInt(vStr[1],"Getworks=");
		s.iAccepted=Parse::GetInt(vStr[1],"Accepted=");
		s.iRejected=Parse::GetInt(vStr[1],"Rejected=");
		s.iHardwareErrors=Parse::GetInt(vStr[1],"Hardware Errors=");
		s.fUtility=Parse::GetDouble(vStr[1],"Utility=");
		s.iDiscarded=Parse::GetInt(vStr[1],"Discarded=");
		s.iStale=Parse::GetInt(vStr[1],"Stale=");
		s.iGetFailures=Parse::GetInt(vStr[1],"Get Failures=");
		s.iLocalWork=Parse::GetInt(vStr[1],"Local Work=");
		s.iRemoteFailures=Parse::GetInt(vStr[1],"Remote Failures=");
		s.iNetworkBlocks=Parse::GetInt(vStr[1],"Network Blocks=");
		s.fTotalMH=Parse::GetDouble(vStr[1],"Total MH=");
		s.fWorkUtility=Parse::GetDouble(vStr[1],"Work Utility=");
		s.fDifficultyAccepted=Parse::GetDouble(vStr[1],"Difficulty Accepted=");
		s.fDifficultyRejected=Parse::GetDouble(vStr[1],"Difficulty Rejected=");
		s.fDifficultyStale=Parse::GetDouble(vStr[1],"Difficulty Stale=");
		s.iBestShare=Parse::GetInt(vStr[1],"Best Share=");
		s.fDeviceHardware=Parse::GetDouble(vStr[1],"Device Hardware%=");
		s.fDeviceRejected=Parse::GetDouble(vStr[1],"Device Rejected%=");
		s.fPoolRejected=Parse::GetDouble(vStr[1],"Pool Rejected%=");
		s.fPoolStale=Parse::GetDouble(vStr[1],"Pool Stale%=");

		//vSummary.push_back(s);
	}
}

void decodeFeedback::decodePools(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	Parse::Substr(msg, &vStr);

	if (!vStr.empty())
	{
		binPools ps;
		ps.tTime=Parse::GetInt(vStr[0],"When=");
		ps.sDesc=Parse::GetStr(vStr[0],"Description=");
		if (vStr.size()>1)
			for(int i=1;i<vStr.size();++i)
			{
				binPool p;
				p.iPOOL=Parse::GetInt(vStr[i],"POOL=");
				p.sURL=Parse::GetStr(vStr[i],"URL=");
				p.sStatus=Parse::GetStr(vStr[i],"Status=");
				p.iPriority=Parse::GetInt(vStr[i],"Priority=");
				p.iQuota=Parse::GetInt(vStr[i],"Quota=");
				p.sLongPoll=Parse::GetStr(vStr[i],"Long Poll=");
				p.iGetworks=Parse::GetInt(vStr[i],"Getworks=");
				p.iAccepted=Parse::GetInt(vStr[i],"Accepted=");
				p.iRejected=Parse::GetInt(vStr[i],"Rejected=");
				p.iWorks=Parse::GetInt(vStr[i],"Works=");
				p.iDiscarded=Parse::GetInt(vStr[i],"Discarded=");
				p.iStale=Parse::GetInt(vStr[i],"Stale=");
				p.iGetFailures=Parse::GetInt(vStr[i],"Get Failures=");
				p.iRemoteFailures=Parse::GetInt(vStr[i],"Remote Failures=");
				p.sUser=Parse::GetStr(vStr[i],"User=");
				p.tLastShareTime=Parse::GetInt(vStr[i],"Last Share Time=");
				p.iDiff1Shares=Parse::GetInt(vStr[i],"Diff1 Shares=");
				p.sProxyType=Parse::GetStr(vStr[i],"Proxy Type=");
				p.sProxy=Parse::GetStr(vStr[i],"Proxy=");
				p.fDifficultyAccepted=Parse::GetDouble(vStr[i],"Difficulty Accepted=");
				p.fDifficultyRejected=Parse::GetDouble(vStr[i],"Difficulty Rejected=");
				p.fDifficultyStale=Parse::GetDouble(vStr[i],"Difficulty Stale=");
				p.fLastShareDifficulty=Parse::GetDouble(vStr[i],"Last Share Difficulty=");
				
				std::string sBool;
				sBool=Parse::GetStr(vStr[i],"Has Stratum=");
				p.bHasStratum=Parse::BoolDetect(sBool);

				sBool=Parse::GetStr(vStr[i],"Stratum Active=");
				p.bStratumActive=p.bHasStratum=Parse::BoolDetect(sBool);

				p.sStratumURL=Parse::GetStr(vStr[i],"Stratum URL=");

				sBool=Parse::GetStr(vStr[i],"Has GBT=");
				p.bHasGBT=Parse::BoolDetect(sBool);

				p.iBestShare=Parse::GetInt(vStr[i],"Best Share=");
				p.fPoolRejected=Parse::GetDouble(vStr[i],"Pool Rejected%=");
				p.fPoolStale=Parse::GetDouble(vStr[i],"Pool Stale%=");

				ps.vPool.push_back(p);
			}
		//vPools.push_back(ps);
	}
}

void decodeFeedback::decodeCoin(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	Parse::Substr(msg, &vStr);

	if (vStr.size()>1)
	{
		binCoin c;

		c.tTime=Parse::GetInt(vStr[0],"When=");
		c.sDesc=Parse::GetStr(vStr[0],"Description=");
		c.sHashMethod=Parse::GetStr(vStr[1],"Hash Method=");
		c.dCurrentBlockTime=Parse::GetDouble(vStr[1],"Current Block Time=");
		c.sCurrentBlockHash=Parse::GetStr(vStr[1],"Current Block Hash=");

		std::string sBool;
		sBool=Parse::GetStr(vStr[1],"LP=");
		c.bLP=Parse::BoolDetect(sBool);
		c.fNetworkDifficulty=Parse::GetDouble(vStr[1],"Network Difficulty=");

		//vCoin.push_back(c);
	}
}

void decodeFeedback::decodeDevs(const std::string& msg)
{
	tVecStr vStr;

	//helper func: parse str to some substr separated by "|" 
	Parse::Substr(msg, &vStr);

	if (vStr.size()>1)
	{
		binDevs d;
		d.tTime=Parse::GetInt(vStr[0],"When=");
		d.sDesc=Parse::GetStr(vStr[0],"Description=");
		for (int i=1;i<vStr.size();++i)
		{
			binGpu g;

			g.iGPU=Parse::GetInt(vStr[i],"GPU=");
			g.sEnabled=Parse::GetStr(vStr[i],"Enabled=");
			g.sStatus=Parse::GetStr(vStr[i],"Status=");
			g.fTemperature=Parse::GetDouble(vStr[i],"Temperature=");
			g.iFanSpeed=Parse::GetInt(vStr[i],"Fan Speed=");
			g.iFanPercent=Parse::GetInt(vStr[i],"Fan Percent=");
			g.iGPUClock=Parse::GetInt(vStr[i],"GPU Clock=");
			g.iMemoryClock=Parse::GetInt(vStr[i],"Memory Clock=");
			g.fGPUVoltage=Parse::GetDouble(vStr[i],"GPU Voltage=");
			g.iGPUActivity=Parse::GetInt(vStr[i],"GPU Activity=");
			g.iPowertune=Parse::GetInt(vStr[i],"Powertune=");
			g.fMHSav=Parse::GetDouble(vStr[i],"MHS av=");
			g.fMHS5s=Parse::GetDouble(vStr[i],"MHS 5s=");
			g.iAccepted=Parse::GetInt(vStr[i],"Accepted=");
			g.iRejected=Parse::GetInt(vStr[i],"Rejected=");
			g.iHardwareErrors=Parse::GetInt(vStr[i],"Hardware Errors=");
			g.fUtility=Parse::GetDouble(vStr[i],"Utility=");
			g.iIntensity=Parse::GetInt(vStr[i],"Intensity=");
			g.tLastSharePool=Parse::GetInt(vStr[i],"Last Share Pool=");
			g.tLastShareTime=Parse::GetInt(vStr[i],"Last Share Time=");
			g.fTotalMH=Parse::GetDouble(vStr[i],"Total MH=");
			g.iDiff1Work=Parse::GetInt(vStr[i],"Diff1 Work=");
			g.fDifficultyAccepted=Parse::GetDouble(vStr[i],"Difficulty Accepted=");
			g.fDifficultyRejected=Parse::GetDouble(vStr[i],"Difficulty Rejected=");
			g.fLastShareDifficulty=Parse::GetDouble(vStr[i],"Last Share Difficulty=");
			g.tLastValidWork=Parse::GetInt(vStr[i],"Last Valid Work=");
			g.fDeviceHardware=Parse::GetDouble(vStr[i],"Device Hardware%=");
			g.fDeviceRejected=Parse::GetDouble(vStr[i],"Device Rejected%=");
			g.iDeviceElapsed=Parse::GetInt(vStr[i],"Device Elapsed=");

			d.vGpu.push_back(g);
		}

		//vDevs.push_back(d);
	}
}