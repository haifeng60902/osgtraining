#include "RigInfo2.h"

#include <assert.h>

#include "QtHlp/QtHlp.h"
#include "core/Parse/parse.h"

RigInfo2::RigInfo2()
{

}

RigInfo2::~RigInfo2()
{

}

void RigInfo2::init(const binSetting& settings)
{
	rigInfo=new QWidget;
	rigInfoLayout=new QVBoxLayout;
	rigInfo->setLayout(rigInfoLayout);

	addGroups(settings);
}

void RigInfo2::addGroups(const binSetting& settings)
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
QWidget* RigInfo2::getWidget()
{
	return rigInfo;
}

void RigInfo2::acceptConnection(QTcpSocket* tcpClientSocket)
{
	//accept new connection
	tMapClient::iterator it=mClient.find(tcpClientSocket);
	if (it!=mClient.end())
		assert(false);
	else
		mClient[tcpClientSocket];
}

void RigInfo2::clientWrite(QTcpSocket* tcpClientSocket)
{
	tMapClient::iterator itClient = mClient.find(tcpClientSocket);
	if (itClient!=mClient.end())
	{
		binClient& cl=itClient->second;
		++cl.iMsgClue;

		int bytesReceived = (int)tcpClientSocket->bytesAvailable();
		QByteArray a=tcpClientSocket->readAll();
		char* ad=a.data();

		std::vector<std::string> msg;

		if(QtHlp::GetStrs(bytesReceived,ad, &msg))
		{
			cl.iWait=iWAIT;
			cl.iMsgSize=msg.size();
			++cl.iMsgRead;

			assert(msg.size()>1);

			for (int i=1;i<msg.size();++i)
				//update gui info
				updateGui(msg[0],msg[i], &cl.iHash);

			cl.iMsgClue=0;
		}
	}
	else
		assert(false);
}

void RigInfo2::clientDisconnected(QTcpSocket* tcpClientSocket)
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

void RigInfo2::updateGui(const std::string& client, const std::string& msg, int* hash)
{
	//update gui info
	eMinerMode mode=Parse::getMode(msg);

	switch (mode)
	{
	case enSummary:
		processSummary(mode, client, msg, hash);
		break;
	default:
		break;
	}
}

void RigInfo2::processSummary(eMinerMode mode, const std::string& client, const std::string& msg, int* hash)
{
	binSummary s;
	Parse::getSummary(msg,&s);

	tMapInfo::iterator itW=mInfo.find(client);
	if (itW!=mInfo.end())
	{
		binInfo& info=itW->second;
		info.iTick=iWAIT;
		(*hash)=s.fMHS5s*1000.0f;

		if (info.vLabel.empty())
		{
			QLabel* l=new QLabel;
			info.vLabel.push_back(l);
			info.lBox->addWidget(l);
		}

		int iAcc=s.fDifficultyAccepted>s.iAccepted?s.fDifficultyAccepted:s.iAccepted;
		int iRej=s.fDifficultyRejected>s.iRejected?s.fDifficultyRejected:s.iRejected;
		int iHw=s.fDeviceRejected>s.iHardwareErrors?s.fDeviceRejected:s.iHardwareErrors;

		std::string sF="(5s):"+std::to_string((int)(s.fMHS5s*1000.0f))
			+"K (avg):"+std::to_string((int)(s.fMHSav*1000.0f))
			+"K/s | A:"+std::to_string(iAcc)
			+" R:"+std::to_string(iRej)
			+" HW:"+std::to_string(iHw)
			+" WU:"+std::to_string(s.fWorkUtility)+"/m";
		
		info.vLabel[0]->setText(sF.c_str());
	}
}

std::string RigInfo2::timerUpdate()
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
	int iHash=0;
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
		{
			iHash+=itClient->second.iHash;
			++itClient;
		}
	}

	std::string sTitle=std::to_string(mClient.size())+"|"+std::to_string(iHash);
	return sTitle;
}