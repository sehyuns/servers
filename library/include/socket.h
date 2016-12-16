//
//	@file	socket.h
//


#ifndef _SOCKET_H_
#define _SOCKET_H_

#pragma once

#pragma comment(lib, "ws2_32")


#include "defs.h"
#include "winsock2.h"


namespace lib
{

	////////////////////////////////////////////////////////////////////////////////
	// @class	Socket
	//
	// @brief	Windows socket에 가장 기본이 되는 클래스로 TCP를 기본 프로토콜로 사용한다.
	//			
	////////////////////////////////////////////////////////////////////////////////
	class Socket
	{
	public:
		Socket();
		~Socket();

	public:
		BOOL			init_address(const string& address_in, short port_in);

		INT32			init_server();
		INT32			start_client();

	public:
		virtual INT32	create();
		virtual VOID	close();

		virtual SOCKET	accept();
		virtual INT32	connect();

		virtual INT32	send(const BYTE* buffer_in, INT32 length_in);
		virtual INT32	recv(const BYTE* buffer_out, INT32& length_out);

	public:
		INT32			enable_nonblock(BOOL is_block=FALSE);

	public:
		SOCKET			get_socket() const				{ return _tcp_socket; }
		VOID			set_socket(const SOCKET& socket_in)		{ _tcp_socket = socket_in; }
		sockaddr_in&	get_address()					{ return _address; }
		BOOL			is_connected()					{ return (INVALID_SOCKET != _tcp_socket); }
		INT32			get_last_error()				{ return _last_socket_error; }

	protected:
		VOID			record_error();

	protected:
		sockaddr_in		_address;
		SOCKET			_tcp_socket;

		INT32			_last_socket_error;
	};

}

#endif