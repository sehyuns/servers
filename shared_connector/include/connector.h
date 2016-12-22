// @file	connector.h
//
//

#ifndef	_CONNECTOR_H_
#define _CONNECTOR_H_	

#pragma once

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
		operator SOCKET()
		{
			return _socket->get_socket();
		}

	private:
		lib::SocketAsync*		_socket;
	};

}

#endif
