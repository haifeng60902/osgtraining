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
		break;
	case enPools:
		processPools(mode, client, msg);
		break;
	case enCoin:
		break;
	case enDevs:
		break;
	case enQuit:
		break;
	default:
		break;
	}

	tMapClient2Worker::iterator it=mClt2Wrk.find(client);
	if (it!=mClt2Wrk.end())
	{

	}
	else
	{
		
	}
	//
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
	if (info->vLabel.size()<4)
	{
		info->vLabel.push_back(new QLabel);//(5s):540.2K (avg):521.2Kh/s | A:38000  R:0  HW:0  WU:497.6/m
		info->vLabel.push_back(new QLabel);//ST: 5  SS: 0 (0.0%)  NB: 348  PA: 0  PR: 45  LW: 9930  GF: 0  RF: 0
		info->vLabel.push_back(new QLabel);//Connected to vtc.poolz.net diff 125 with stratum as user dbhec.7970x2
		info->vLabel.push_back(new QLabel);//Block: f2ff73a0...  Diff:227  Started: [11:14:16]  Best share: 101K

		info->lBox->addWidget(info->vLabel[0]);
		info->lBox->addWidget(info->vLabel[1]);
		info->lBox->addWidget(info->vLabel[2]);
		info->lBox->addWidget(info->vLabel[3]);
	}

	int k=0;
	for (int i=1;i<ps.vPool.size();++i)
		if (ps.vPool[i].iPriority==0)
			k=i;

	std::string sPoolInfo="Connected to "+ps.vPool[k].sStratumURL+" diff "+
		std::to_string((int)ps.vPool[k].fLastShareDifficulty)+"with stratum as user "+ps.vPool[k].sUser;

	//stratum url last share diff
	info->vLabel[2]->setText(sPoolInfo.c_str());
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
				info.lBox->removeWidget(info.vLabel[i]);
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
		}
	}
}