// @file	singleton.h
//
//

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#pragma once

namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	Singleton
	//
	// @brief	
	//			
	////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class Singleton
	{
	public:
		static T*	get_instance()
		{
			if (nullptr == _instance)
				_instance = new T();
			return _instance;
		}

	public:
		Singleton()		{}
		virtual ~Singleton()	{}

	protected:
		static T*		_instance;
	};

	template<typename T>
	T*	Singleton<T>::_instance = nullptr;
}

#endif
