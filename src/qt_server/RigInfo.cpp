#include "RigInfo.h"

#include "core/Parse/parse.h"

RigInfo::RigInfo()
{

}

RigInfo::~RigInfo()
{

}

void RigInfo::init(const binSetting& settings)
{
	rigInfo=new QWidget;
	rigInfoLayout=new QVBoxLayout;
	rigInfo->setLayout(rigInfoLayout);

	addGroups(settings);
}

void RigInfo::addGroups(const binSetting& settings)
{
	int row=settings.vWorker.size()/settings.iColumn;
	int last=settings.vWorker.size()%settings.iColumn;
	if (last>0)
		++row;

	int k=0;
	for (int i=0;i<row;++i)
	{
		binRigLine line;
		line.lineLayout=new QHBoxLayout;
		rigInfoLayout->addLayout(line.lineLayout);
		for (int j=0;j<settings.iColumn;++j)
		{
			QGroupBox* box=new QGroupBox;
			QVBoxLayout* layoutBox=new QVBoxLayout;
			box->setTitle(settings.vWorker[k].sWorker.c_str());
			box->setLayout(layoutBox);

			line.vGroupBox.push_back(box);
			line.vLayoutInGroupBox.push_back(layoutBox);

			line.lineLayout->addWidget(box);

			mInfo[settings.vWorker[k].sWorker].lBox=layoutBox;
			mInfo[settings.vWorker[k].sWorker].gBox=box;

			++k;

			if (k==settings.vWorker.size())
				break;
		}
		vRigLine.push_back(line);
	}
}

//get custom widget
QWidget* RigInfo::getWidget()
{
	return rigInfo;
}

void RigInfo::update(const std::string& client, const std::string& msg)
{
	//update gui info
	eMinerMode mode=Parse::getMode(msg);

	switch (mode)
	{
	case enFirtMsg:
		break;
	case enSummary:
		processSummary(mode, client, msg);
		break;
	case enPools:
		processPools(mode, client, msg);
		break;
	//case enCoin:
	//	processCoin(mode, client, msg);
	//	break;
	case enDevs:
		processDevs(mode, client, msg);
		break;
	case enQuit:
		break;
	default:
		break;
	}
}

void RigInfo::processPools(eMinerMode mode, const std::string& client, const std::string& msg)
{
	binPools ps;
	Parse::getPools(msg,&ps);
	if (!ps.vPool.empty())
	{
		//for convert purpose
		std::string sWorker=ps.vPool[0].sUser;
		mClt2Wrk[client]=sWorker;
		
		//find out info box
		tMapInfo::iterator it=mInfo.find(sWorker);
		if (it!=mInfo.end())
			//fill main info
			fillPoolInfo(&it->second, ps, msg);
	}
}

void RigInfo::fillPoolInfo(binInfo* info, const binPools& ps, const std::string& msg)
{
	//fill main info
	info->iTick=DISCONNECT_WAIT;
	if (info->vLabel.size()<2)
	{
		info->vLabel.push_back(new QLabel);//(5s):540.2K (avg):521.2Kh/s | A:38000  R:0  HW:0  WU:497.6/m
		info->vLabel.push_back(new QLabel);//Connected to vtc.poolz.net diff 125 with stratum as user dbhec.7970x2
		
		info->lBox->addWidget(info->vLabel[0]);
		info->lBox->addWidget(info->vLabel[1]);
	}

	int k=0;
	for (int i=1;i<ps.vPool.size();++i)
		if (ps.vPool[i].iPriority==0)
			k=i;

	std::string sPoolInfo=ps.vPool[k].sStratumURL+" diff "+
		std::to_string((int)ps.vPool[k].fLastShareDifficulty)+" user "+ps.vPool[k].sUser;

	//stratum url last share diff
	info->vLabel[1]->setText(sPoolInfo.c_str());
}

void RigInfo::processSummary(eMinerMode mode, const std::string& client, const std::string& msg)
{
	binSummary s;
	Parse::getSummary(msg,&s);
	tMapClient2Worker::iterator it=mClt2Wrk.find(client);
	if (it!=mClt2Wrk.end())
	{
		//record is present
		std::string sWorker=it->second;

		tMapInfo::iterator itW=mInfo.find(sWorker);
		if (itW!=mInfo.end())
		{
			binInfo& info=itW->second;
			info.iTick=DISCONNECT_WAIT;
			if (info.vLabel.size()>1)
			{
				std::string sF="(5s):"+std::to_string((int)(s.fMHS5s*1000.0f))
					+"K (avg):"+std::to_string((int)(s.fMHSav*1000.0f))
					+"K/s | A:"+std::to_string((int)s.fDifficultyAccepted)
					+" R:"+std::to_string((int)s.fDifficultyRejected)
					+" HW:"+std::to_string((int)s.fDeviceRejected)
					+" WU:"+std::to_string((int)s.fWorkUtility)+"/m";
				info.vLabel[0]->setText(sF.c_str());
			}
		}
	}
}

void RigInfo::processCoin(eMinerMode mode, const std::string& client, const std::string& msg)
{
	binCoin c;
	Parse::getCoin(msg,&c);
	tMapClient2Worker::iterator it=mClt2Wrk.find(client);
	if (it!=mClt2Wrk.end())
	{
		//record is present
		std::string sWorker=it->second;

		tMapInfo::iterator itW=mInfo.find(sWorker);
		if (itW!=mInfo.end())
		{
			binInfo& info=itW->second;
			info.iTick=DISCONNECT_WAIT;
			if (info.vLabel.size()>2)
			{
				//hash Diff:(netdiff) 
				std::string sL="Block: "+c.sCurrentBlockHash.substr(0,9)+"... Diff:"
					+std::to_string((int)c.fNetworkDifficulty);
				info.vLabel[3]->setText(sL.c_str());
			}
		}
	}
}

void RigInfo::processDevs(eMinerMode mode, const std::string& client, const std::string& msg)
{
	binDevs d;
	Parse::getDevs(msg,&d);
	tMapClient2Worker::iterator it=mClt2Wrk.find(client);
	if (it!=mClt2Wrk.end())
	{
		//record is present
		std::string sWorker=it->second;

		tMapInfo::iterator itW=mInfo.find(sWorker);
		if (itW!=mInfo.end())
		{
			binInfo& info=itW->second;
			info.iTick=DISCONNECT_WAIT;
			
			{
				for (int i=0;i<d.vGpu.size();++i)
				{
					int ind=2+i;
					if (info.vLabel.size()<=ind)
					{
						QLabel* l=new QLabel;
						info.vLabel.push_back(l);
						info.lBox->addWidget(l);
					}

					std::string sG="GPU "+std::to_string(d.vGpu[i].iGPU)+"("
						+std::to_string((int)d.vGpu[i].iGPUClock)+"/"
						+std::to_string((int)d.vGpu[i].iMemoryClock)+"): "
						+std::to_string((int)d.vGpu[i].fTemperature)
						+"C "+std::to_string(d.vGpu[i].iFanSpeed)+"RPM("+std::to_string(d.vGpu[i].iFanPercent)+"%)"
						+" | "+std::to_string((int)(d.vGpu[i].fMHS5s*1000.0f))+"K/"
						+std::to_string((int)(d.vGpu[i].fMHSav*1000.0f))+"Kh/s | A:"
						+std::to_string((int)(d.vGpu[i].fDifficultyAccepted))+" R:"
						+std::to_string((int)(d.vGpu[i].fDifficultyRejected))+" HW:"
						+std::to_string((int)(d.vGpu[i].fDeviceRejected))+" I:"
						+std::to_string(d.vGpu[i].iIntensity);
					info.vLabel[2+i]->setText(sG.c_str());
				}
			}
		}
	}
}

void RigInfo::timerUpdate()
{
	//detect disconnect workers
	tMapInfo::iterator it=mInfo.begin();
	for (;it!=mInfo.end();++it)
	{
		binInfo& info=it->second;
		--info.iTick;
		if (info.iTick<1)
		{
			//worker is disconnected
			info.iTick=0;
			for (int i=0;i<info.vLabel.size();++i)
			{
				info.lBox->removeWidget(info.vLabel[i]);
				delete info.vLabel[i];
			}
			info.vLabel.clear();
			
			//delete record from map
			tMapClient2Worker::iterator itW=mClt2Wrk.begin();
			while (itW!=mClt2Wrk.end())
			{
				if (itW->second==it->first)
				{
					mClt2Wrk.erase(itW);
					itW=mClt2Wrk.end();
				}
				else
					++itW;
			}

			std::string sTi=it->first;
			info.gBox->setTitle(sTi.c_str());
		}
		else
		{
			std::string sTi=it->first+"|"+std::to_string(info.iTick);
			info.gBox->setTitle(sTi.c_str());
		}
	}
}