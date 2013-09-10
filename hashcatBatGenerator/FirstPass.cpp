#include "FirstPass.h"

#include <fstream>
#include <sstream>

FirstPass::FirstPass()
{

}

FirstPass::~FirstPass()
{

}

void FirstPass::Init(const binInput& in)
{
	pIn=&in;

	//заполнить вектор хэшей
	FillHashVec();

	//сгенерить текст батника
	GenBatFirst();
	GenBatRestore();
}

void FirstPass::Save()
{
	std::ofstream fp;
	fp.open("FirstPass.bat", std::ios::out|std::ios::binary);
	fp<<sResFirst;
	fp.close();

	std::ofstream fr;
	fr.open("RestorePass.bat", std::ios::out|std::ios::binary);
	fr<<sResRestore;
	fr.close();
}

void FirstPass::FillHashVec()
{
	//заполнить вектор хэшей
	std::ifstream ifs(pIn->hashFile);
	int iL=0;
	while(!ifs.eof())
	{
		std::string line;
		std::getline(ifs,line);
		vHash.push_back(line);
	}
}

void FirstPass::GenBatFirst()
{
	//сгенерить текст батника
	sResFirst.clear();
	for(int i=0;i<vHash.size();++i)
	{
		std::stringstream ssS;
		ssS<<(int)pIn->statusTime;
		std::string sS(ssS.str());

		std::stringstream ssR;
		ssR<<(int)pIn->restoreTime;
		std::string sR(ssR.str());

		std::stringstream ssT;
		ssT<<(int)pIn->runTime;
		std::string sT(ssT.str());

		sResFirst+=pIn->exeFile+" "+vHash[i]+" --force --gpu-temp-disable --gpu-loops=1024 --status --status-timer="+sS
			+" --outfile="+pIn->passFile+" --session="+vHash[i]+" --restore-timer="+sR
			+" --runtime="+sT+"\n";
	}
}

void FirstPass::GenBatRestore()
{
	sResRestore.clear();
	for(int i=0;i<vHash.size();++i)
	{
		sResRestore+=pIn->exeFile+" --restore --session="+vHash[i]+"\n";
	}
}