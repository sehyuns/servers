// @file	socket.cpp
// 
//


#include "socket.h"
#include "error_defs.h"

#include <WS2tcpip.h>


namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	Socket::Socket() : _tcp_socket(INVALID_SOCKET), _last_socket_error(0)
	{
		memset(&_address, 0, sizeof(_address));
	}


	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	Socket::~Socket()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	BOOL	Socket::init_address(const string& address_in, short port_in)
	{
		memset(&_address, 0, sizeof(_address));
		_address.sin_family = AF_INET;
		_address.sin_port = htons(port_in);
		inet_pton(AF_INET, address_in.c_str(), &_address.sin_addr.s_addr);

		return TRUE;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	Socket::init_server()
	{
		INT32 result = create();
		if (ERR_SUCCEEDED != result)
			return result;

		result = bind(_tcp_socket, (struct sockaddr*)&_address, sizeof(_address));
		if (SOCKET_ERROR == result)
		{
			record_error();
			return ERR_SOCKET_BIND;
		}

		CHAR opt_val = 1;
		result = setsockopt(_tcp_socket, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val));
		if (SOCKET_ERROR == result)
		{
			record_error();
			return ERR_SOCKET_OPTION;
		}

		result = listen(_tcp_socket, 5);
		if (SOCKET_ERROR == result)
		{
			record_error();
			return ERR_SOCKET_LISTEN;
		}

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	Socket::start_client()
	{
		INT32 result = create();
		if (ERR_SUCCEEDED != result)
			return result;

		result = connect();
		if (ERR_SUCCEEDED == result)
			return result;

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	Socket::close()
	{
		if (INVALID_SOCKET != _tcp_socket)
		{
			closesocket(_tcp_socket);
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SOCKET Socket::accept()
	{
		SOCKET client = ::accept(_tcp_socket, nullptr, nullptr);
		if (INVALID_SOCKET == client)
		{
			record_error();
			return INVALID_SOCKET;
		}

		return client;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32 Socket::connect()
	{
		if (0 == _address.sin_family)
			return ERR_SOCKET_ADDRESS;

		if (SOCKET_ERROR == ::connect(_tcp_socket, (struct sockaddr*)&_address, sizeof(_address)))
		{
			record_error();
			return ERR_SOCKET_CONNECT;
		}
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32 Socket::send(const BYTE * buffer_in, INT32 length_in)
	{
		INT32 result = ::send(_tcp_socket, (CHAR*)buffer_in, length_in, 0);
		if (SOCKET_ERROR == result)
		{
			record_error();
			return ERR_SOCKET_SEND;
		}
		return ERR_SUCCEEDED;
	}

	INT32 Socket::recv(const BYTE * buffer_out, INT32 & length_out)
	{
		INT32 result = ::recv(_tcp_socket, (CHAR*)buffer_out, length_out, 0);
		if (SOCKET_ERROR == result)
		{
			record_error();
			return ERR_SOCKET_RECV;
		}
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	Socket::enable_nonblock(BOOL is_block)
	{
		u_long opt_val = 0;
		if (FALSE == is_block)
			opt_val = 1;

		INT32 result = ioctlsocket(_tcp_socket, FIONBIO, &opt_val);
		if (NO_ERROR != result)
		{
			_last_socket_error = result;
			return ERR_SOCKET_IOCTL;
		}

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID Socket::record_error()
	{
		_last_socket_error = WSAGetLastError();
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	Socket::create()
	{
		_tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == _tcp_socket)
		{
			record_error();
			return ERR_SOCKET_MAKE;
		}

		return ERR_SUCCEEDED;
	}

}