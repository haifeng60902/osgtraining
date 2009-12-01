#include "xmlBranchLoad.h"

xmlBranchLoad::xmlBranchLoad() : m_pData( NULL )
{

}

xmlBranchLoad::~xmlBranchLoad()
{

}

void xmlBranchLoad::ParseXml( ticpp::Node* pNode , binBranch *_data )
{
	//разбор xml и заполнение бинарных данных
	m_pData = _data;

	//перейти к настройкам приложения
	DecodeSettings( pNode );
}

void xmlBranchLoad::DecodeSettings( ticpp::Node* pNode )
{
	//перейти к настройкам приложения

}