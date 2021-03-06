// @file	connector.h
//
//

#ifndef	_CONNECTOR_H_
#define _CONNECTOR_H_	

#pragma once

#include "connector_defs.h"

#include "socket_async.h"
#include "singleton.h"


namespace connector
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	Connector
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class Connector
	{
	public:
		Connector();
		~Connector();

	public:
		INT32			initialize(string& address_in, SHORT port_in);
		VOID			close();

	public:
		operator SOCKET()					{ return _socket.get_socket(); }

	private:
		lib::SocketAsync		_socket;
	};

}

#endif
