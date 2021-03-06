// @file	base_connector.h
//
//

#ifndef _BASE_CONNECTOR_H_
#define _BASE_CONNECTOR_H_

#pragma once

#include "shared_defs.h"

#include "thread.h"
#include "winsock_env.h"

namespace lib
{
	class SocketAsync;
	class Iocp;
}

namespace shared
{
	class Session;
}

namespace shared
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	BaseConnector
	//
	// @brief	client side의 connector. 다중 접속에 관련해서 지원한다. SessionManager와 연동한다.
	//			
	////////////////////////////////////////////////////////////////////////////////
	class BaseConnector : public lib::Thread<BaseConnector>, public lib::WinsockEnv
	{
	public:
		BaseConnector();
		~BaseConnector();

	public:
		INT32		initialize();
		VOID		close();

		INT32		worker_thread();

	public:
		INT32		add_connection(const string& address_in, SHORT port);

	private:
		lib::Iocp*		_iocp;

		Session*		_session;
	};
}

#endif
