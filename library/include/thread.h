// @file	thread.h
//
//

#ifndef _THREAD_H_
#define _THREAD_H_

#pragma once

#include "defs.h"


namespace lib
{

	////////////////////////////////////////////////////////////////////////////////
	// @class	Thread
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class Thread
	{
	public:
		typedef	INT32	(*ThreadFunc)();
	public:
		Thread();
		virtual ~Thread();

		INT32			initialize();
		VOID			close();

		virtual INT32	worker_thread() = 0;

	public:
		INT32			start_thread();
		INT32			end_thread();

	private:
		HANDLE		_thread_handle;
	};
}

#endif
