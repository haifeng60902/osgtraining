#ifndef _XML_TMPL_H_
#define _XML_TMPL_H_

#include "ticpp.h"

template < class Bin , class Load , class Save >
class xmlTmpl
{
public:
	xmlTmpl(){};
	~xmlTmpl(){};

	//������������� ������
	void Init( ticpp::Node* pNode )
	{
		//������� ��������� ������ ��� �������� xml
		Load _load;

		//������ xml � ���������� �������� ������
		_load.ParseXml( pNode , &m_Data );
	};

	//�������� xml ��� � ��������������� �������
	ticpp::Node* GetXmlData()
	{
		//�������� xml ��� � ��������������� �������
		Save _save;

		return _save.GetXmlData( m_Data );
	};

	//�������� ������ �� ������
	Bin& GetData(){ return m_Data; };

private:
	Bin m_Data;
};

#endif	//_XML_TMPL_H_