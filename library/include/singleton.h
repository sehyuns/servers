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
				return nullptr;
			return _instance;
		}

	public:
		static VOID	create()
		{
			if (nullptr == _instance)
				_instance = new T();
		}

		static VOID	destroy()
		{
			if (nullptr != _instance)
				delete _instance;
			_instance = nullptr;
		}

	private:
		static T*		_instance;
	};

	template<typename T>
	T*	Singleton<T>::_instance = nullptr;
}

#endif
