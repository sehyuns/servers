// @file	session.h
//
//

#ifndef _SESSION_H_
#define _SESSION_H_

#pragma once

#include "shared_defs.h"

#include "socket_async.h"
#include "packet_buffer.h"


namespace shared
{
	////////////////////////////////////////////////////////////////////////////////
	// @class
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class Session
	{
	public:
		Session();
		~Session();

	public:
		INT32			initialize(const SOCKET& socket_in);
		VOID			close();

		INT32			recv();
		INT32			send(const BYTE* buffer_in, INT32 length_in);

	public:
		lib::SocketAsync*	get_socket()			{ return &_socket; }
		CHAR*				get_recv_buffer()		{ return _recv_buffer.buf; }

	private:
		lib::SocketAsync	_socket;

		lib::PacketBuffer	_recv_buffer;
		lib::PacketBuffer	_send_buffer;
	};
}

#endif
