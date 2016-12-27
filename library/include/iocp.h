// @file	iocp.h
//
//

#ifndef _IOCP_H_
#define _IOCP_H_

#pragma once

#include "socket.h"

namespace lib
{
	class Socket;
}

namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	// @class
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class Iocp
	{
	public:
		Iocp();
		~Iocp();

	public:
		INT32		initialize();
		VOID		close();

		INT32		create_new_session(const SOCKET& socket_in);

		INT32		pop_income(INT32& key_out, UINT32& bytes_out, LPOVERLAPPED* overlapped_out);

		INT32		push_forcely(INT32 key_in, OVERLAPPED* overlapped_in);

	private:
		HANDLE		_handle;

		INT32		_last_error;
	};

}

#endif