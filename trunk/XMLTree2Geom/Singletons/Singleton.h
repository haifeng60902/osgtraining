#ifndef _SINGLETON_
#define _SINGLETON_

template<typename T> class Singleton
{
public:
	static T& Instance()
	{
		static T theSingleInstance; // � ������ T ���� ����������� �� ���������
		return theSingleInstance;
	}
};

#endif //_SINGLETON_