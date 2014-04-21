#include "QtHlp/QtHlp.h"

#include <vector>
#include <QHostAddress>

bool QtHlp::GetStr(QTcpSocket* sock, std::string* str, std::string* loc)
{
	bool bRes=false;
	int bytesReceived = (int)sock->bytesAvailable();
	if (bytesReceived<2)
		return bRes;

	QByteArray a=sock->readAll();
	char* ad=a.data();
	quint16 si=*((quint16*)ad);
	if (si==bytesReceived)
	{
		char sL=ad[2];
		std::string s;
		*loc=std::string(&ad[3], sL);
	
		*str=std::string(&ad[3+sL], si-3-sL);
		bRes=true;
	}

	return bRes;
}

void QtHlp::WriteStr(QTcpSocket* sock, const std::string& s)
{
	std::vector<char> data;
	std::string sLoc=sock->localAddress().toString().toStdString();
	data.resize(s.size()+2+sLoc.size()+1);
	*(quint16*)(&data[0])=s.size()+2+sLoc.size()+1;
	data[2]=sLoc.size();
	memcpy(&data[3],&sLoc[0],sLoc.size());


	memcpy(&data[3+sLoc.size()],&s[0],s.size());
	sock->write(&data[0],data.size());
}

bool QtHlp::GetStrs(int bytesReceived, char* data, std::vector<std::string>* vs)
{

	bool bRes=false;
	if (bytesReceived<2)
		return bRes;

	quint16 size=*((quint16*)data);
	if (size==bytesReceived)
	{
		quint16 num_rec=*((quint16*)&data[2]);
		vs->resize(num_rec);
		for (int i=0;i<num_rec;++i)
		{
			quint16 rec_size=*((quint16*)&data[4+i*2]);
			vs->at(i).resize(rec_size);
		}

		int iOffset=4+num_rec*2;
		for (int i=0;i<num_rec;++i)
		{
			memcpy( &(*vs)[i], &data[iOffset],vs->at(i).size());
			iOffset+=vs->at(i).size();
		}
	}

	return bRes;
}

void QtHlp::WriteStrs(const std::vector<std::string>& vs, std::vector<char>& data)
{
	//calc new size
	int iSize=4+vs.size()*2;
	for (int i=0;i<vs.size();++i)
		iSize+=vs[i].size();

	data.resize(iSize);

	//overall size 
	*(quint16*)(&data[0])=iSize;

	//number of records
	*(quint16*)(&data[2])=vs.size();

	//fill individual size
	for (int i=0;i<vs.size();++i)
		*(quint16*)(&data[4+i*2])=vs[i].size();

	//copy strings
	int iOffset=4+vs.size()*2;
	for (int i=0;i<vs.size();++i)
	{
		memcpy(&data[iOffset],&vs[i],vs[i].size());
		iOffset+=vs[i].size();
	}
}

//generate random string
void QtHlp::rndStr(std::string* str, int len_from, int len_to)
{
	quint16 iSize=len_from+(len_to-len_from)*(float)rand()/(float)RAND_MAX;
	str->resize(iSize);
	for (int i=0;i< iSize;++i)
		str->at(i)=64+24*(float)rand()/(float)RAND_MAX;
}