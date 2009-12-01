#ifndef _XML_TMPL_H_
#define _XML_TMPL_H_

#include "tinyxml.h"

template < class Bin , class Load , class Save >
class xmlTmpl
{
public:
	xmlTmpl(){};
	~xmlTmpl(){};

	//������������� ������
	void Init( TiXmlElement* root )
	{
		//������� ��������� ������ ��� �������� xml
		Load _load;

		//������ xml � ���������� �������� ������
		_load.ParseXml( root , &m_Data );
	};

	//�������� xml ��� � ��������������� �������
	TiXmlElement* GetXmlData()
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