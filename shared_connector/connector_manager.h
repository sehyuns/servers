// @file	connector_manager.h
//
//

#ifndef _CONNECTOR_MANAGER_H_
#define _CONNECTOR_MANAGER_H_

#pragma once

#include "connector_defs.h"

#include "singleton.h"


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
	// @class	ConnectorManager
	//
	// @brief	
	//			
	////////////////////////////////////////////////////////////////////////////////
	class ConnectorManager : public lib::Singleton<ConnectorManager>
	{
	public:
		INT32		initialize(string& address_in, SHORT port_in);
		VOID		close();

	public:
		INT32		worker_thread();

	protected:
		ConnectorManager();
		~ConnectorManager();

	private:
		lib::Iocp*	_iocp;

		VOID*		_close_event;
		BOOL		_is_continue;

		Connector*	_session_connector;
	};
}

#endif
