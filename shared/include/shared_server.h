// @file	shared_server.h
//
//

#ifndef _SHARED_SERVER_H_
#define _SHARED_SERVER_H_

#pragma once

#include "shared_defs.h"

#include "winsock_env.h"


namespace lib
{
	class Iocp;
	class SocketAsync;
}

namespace shared
{

	////////////////////////////////////////////////////////////////////////////////
	// @class	SharedServer
	//
	// @brief	
	//			
	////////////////////////////////////////////////////////////////////////////////
	class SharedServer : public lib::WinsockEnv
	{
	public:
		SharedServer();
		~SharedServer();

	public:
		INT32			initialise(const string& address_in, SHORT port_in);
		VOID			close();

		INT32			start();

	
		INT32			acceptor_thread();
		INT32			worker_thread();

	private:
		lib::SocketAsync*	_listen_socket;
		lib::Iocp*			_iocp;

		VOID*				_close_event;
		BOOL				_is_continue;
	};

}

#endif
