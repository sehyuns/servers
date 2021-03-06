// @file	connector_manager.h
//
//

#ifndef _CONNECTOR_MANAGER_H_
#define _CONNECTOR_MANAGER_H_

#pragma once

#include "connector_defs.h"

#include "singleton.h"
#include "winsock_env.h"

namespace lib
{
	class Iocp;
}

namespace connector
{
	class Connector;
}

namespace connector
{
	////////////////////////////////////////////////////////////////////////////////
	// @class
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class ConnectorManager : public lib::WinsockEnv, public lib::Singleton<ConnectorManager>
	{
	public:
		INT32			initialize(string& address_in, SHORT port_in);
		VOID			close();

		INT32			worker_thread();

	public:
		ConnectorManager();
		~ConnectorManager();

	private:
		lib::Iocp*		_iocp;
		Connector*		_session_connector;

		BOOL			_is_continue;
		HANDLE			_close_event;
	};
}

#endif
