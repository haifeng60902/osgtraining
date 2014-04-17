#include "RigInfo.h"

#include "core/Parse/parse.h"
#include "QtHlp/QtHlp.h"

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
	iWAIT=settings.iWait;

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

void RigInfo::acceptConnection(QTcpSocket* tcpClientSocket)
{
	//accept new connection
	mClient[tcpClientSocket];
}

void RigInfo::clientWrite(QTcpSocket* tcpClientSocket)
{
	//read message from client
	tMapClient::iterator itClient = mClient.find(tcpClientSocket);
	if (itClient!=mClient.end())
	{
		binClient& cl=itClient->second;
		++cl.iMsgClue;
	
		std::string sMsg,sClient;
		if(QtHlp::GetStr(tcpClientSocket,&sMsg,&sClient))
		{
			cl.iWait=iWAIT;
			cl.iMsgSize=sMsg.size();
			++cl.iMsgRead;

			//update gui info
			update(sClient,sMsg);

			cl.iMsgClue=0;

			std::string sResp("ok=");
			sResp=sResp+std::to_string(cl.iMsgSize);
			QtHlp::WriteStr(tcpClientSocket,sResp);
		}
	}
}

void RigInfo::clientDisconnected(QTcpSocket* tcpClientSocket)
{
	//client disconnected
	tMapClient::iterator itClient = mClient.find(tcpClientSocket);
	if (itClient!=mClient.end())
	{
		binClient& cl=itClient->second;
		tMapInfo::iterator itInfo=mInfo.find(cl.sClient);
		if (itInfo!=mInfo.end())
		{
			//remove all labels from GroupBox
			binInfo& info=itInfo->second;

			info.iTick=0;
			for (int i=0;i<info.vLabel.size();++i)
			{
				info.lBox->removeWidget(info.vLabel[i]);
				delete info.vLabel[i];
			}
			info.vLabel.clear();
		}

		mClient.erase(itClient);
	}
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
		//std::string sWorker=ps.vPool[0].sUser;
		//mClt2Wrk[client]=sWorker;
		
		//find out info box
		tMapInfo::iterator it=mInfo.find(client);
		if (it!=mInfo.end())
			//fill main info
			fillPoolInfo(&it->second, ps, msg);
	}
}

void RigInfo::fillPoolInfo(binInfo* info, const binPools& ps, const std::string& msg)
{
	//fill main info
	info->iTick=iWAIT;
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

	tMapInfo::iterator itW=mInfo.find(client);
	if (itW!=mInfo.end())
	{
		binInfo& info=itW->second;
		info.iTick=iWAIT;
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

void RigInfo::processCoin(eMinerMode mode, const std::string& client, const std::string& msg)
{
	binCoin c;
	Parse::getCoin(msg,&c);

	tMapInfo::iterator itW=mInfo.find(client);
	if (itW!=mInfo.end())
	{
		binInfo& info=itW->second;
		info.iTick=iWAIT;
		if (info.vLabel.size()>2)
		{
			//hash Diff:(netdiff) 
			std::string sL="Block: "+c.sCurrentBlockHash.substr(0,9)+"... Diff:"
				+std::to_string((int)c.fNetworkDifficulty);
			info.vLabel[3]->setText(sL.c_str());
		}
	}
}

void RigInfo::processDevs(eMinerMode mode, const std::string& client, const std::string& msg)
{
	binDevs d;
	Parse::getDevs(msg,&d);
	
	tMapInfo::iterator itW=mInfo.find(client);
	if (itW!=mInfo.end())
	{
		binInfo& info=itW->second;
		info.iTick=iWAIT;
			
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

void RigInfo::timerUpdate()
{
	//detect disconnect workers
	tMapInfo::iterator itInfo=mInfo.begin();
	for (;itInfo!=mInfo.end();++itInfo)
	{
		binInfo& info=itInfo->second;
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
			
			std::string sTi=itInfo->first;
			info.gBox->setTitle(sTi.c_str());
		}
		else
		{
			std::string sTi=itInfo->first+"|"+std::to_string(info.iTick);
			info.gBox->setTitle(sTi.c_str());
		}
	}

	//clean up sockets
	tMapClient::iterator itClient=mClient.begin();
	while (itClient!=mClient.end())
	{
		--itClient->second.iWait;
		if (itClient->second.iWait<1)
		{
			itClient->first->deleteLater();

			itClient=mClient.erase(itClient);
		}
		else
			++itClient;
	}
}