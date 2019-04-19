#pragma once

template <typename T>
class Singleton
{
private:
	static T* p;
public:

	static T* Instance()
	{
		if (!p)
			p = new T;

		return p;
	}

	static void Release()
	{
		if (p)
			delete p;
		p = nullptr;
	}
};

template <typename T>
T* Singleton<T>::p = nullptr;