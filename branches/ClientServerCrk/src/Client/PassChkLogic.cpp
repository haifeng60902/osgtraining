#include "PassChkLogic.h"

PassChkLogic::PassChkLogic()
{

}

PassChkLogic::~PassChkLogic()
{

}

void PassChkLogic::Init(const std::string& sNode)
{
	//set node name
	this->sNode=sNode;

	//first time init output buffer
	FirstTimeInit();
}

void PassChkLogic::FirstTimeInit()
{
	//first time init output buffer

}