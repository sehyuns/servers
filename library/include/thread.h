// @file	thread.h
//
//

#ifndef _THREAD_H_
#define _THREAD_H_

#pragma once

#include "defs.h"

#include <unordered_map>

namespace lib
{

	////////////////////////////////////////////////////////////////////////////////
	// @class	Thread
	//
	// @brief	
	//			
	////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class Thread
	{
	public:
		struct ThreadArg
		{
			ThreadArg(void* obj_in, const string& name_in) : _object(obj_in), _name(name_in) {}

			void*		_object;
			string		_name;
		};

		typedef		INT32	(T::*ThreadFunc)();

	public:
		Thread();
		virtual ~Thread();

		INT32			initialize();
		VOID			close();

	public:
		INT32			register_thread(const string& name_in, ThreadFunc func_in, SHORT thread_num_in=1);

		INT32			start_all_threads();
		INT32			stop_all_threads();

		INT32			start_thread(const string& name_in);
		INT32			stop_thread(const string& name_in);

	public:
		static unsigned __stdcall thread_main(void* argument);
		INT32			run_thread(const string& name_in);

	private:
		HANDLE		_thread_handle;

		typedef	std::vector<HANDLE>							THandleList;
		typedef	std::unordered_map<string, THandleList>		THandleMap;
		THandleMap	_handle_map;

		typedef	std::unordered_map<string, ThreadArg>		TArgumentMap;
		TArgumentMap	_argument_map;

		typedef	std::unordered_map<string, ThreadFunc>		TFuncMap;
		TFuncMap		_func_map;
	};
}

#endif
