#ifndef _SINGLETON_
#define _SINGLETON_

template<typename T> class Singleton
{
public:
	static T& Instance()
	{
		static T theSingleInstance; // у класса T есть конструктор по умолчанию
		return theSingleInstance;
	}
};

#endif //_SINGLETON_