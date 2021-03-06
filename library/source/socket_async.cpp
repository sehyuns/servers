// @file	socket_async.cpp
//
//

#include "socket_async.h"

#include "error_defs.h"
#include "overlapped.h"

namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SocketAsync::SocketAsync() : _recv_buf(nullptr)
	{
		
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SocketAsync::~SocketAsync()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SocketAsync::create()
	{
		_tcp_socket = WSASocket(PF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET == _tcp_socket)
		{
			record_error();
			return ERR_SOCKET_MAKE;
		}

		_recv_buf = new Overlapped();
		_send_buf = new Overlapped();
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	SocketAsync::close()
	{
		Super::close();

		if (nullptr != _recv_buf)
			delete _recv_buf;

		_recv_buf = nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SOCKET SocketAsync::accept()
	{
		SOCKET client = WSAAccept(_tcp_socket, nullptr, nullptr, nullptr, 0);
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
	INT32 SocketAsync::connect()
	{
		if (0 == _address.sin_family)
			return ERR_SOCKET_ADDRESS;

		INT32 result = WSAConnect(_tcp_socket, (struct sockaddr*)&_address, sizeof(_address), nullptr, nullptr, nullptr, nullptr);
		if (NO_ERROR != result)
		{
			record_error();
			return ERR_SOCKET_CONNECT;
		}
		return ERR_SUCCEEDED;
	}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//INT32 SocketAsync::send(const BYTE * buffer_in, INT32 length_in)
	//{
	//	_send_buf->reset();
	//	_send_buf->set_type(EOTYPE_SEND);

	//	_send_buf->set_buffer(buffer_in, length_in);

	//	DWORD flag = 0;
	//	INT32 result = WSASend(_tcp_socket, _send_buf->get_wsa_buf(), length_in, 
	//						  (LPDWORD)_send_buf->get_total_sent(), flag, 
	//						  (LPWSAOVERLAPPED)_send_buf, nullptr);
	//	if (SOCKET_ERROR == result)
	//	{
	//		record_error();
	//		return ERR_SOCKET_SEND;
	//	}
	//	return ERR_SUCCEEDED;
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//INT32 SocketAsync::recv(const BYTE* buffer_out, INT32& length_out)
	//{
	//	_recv_buf->reset();
	//	_recv_buf->set_type(EOTYPE_RECV);
	//	DWORD flag = 0;
	//	INT32 result = WSARecv(_tcp_socket, _recv_buf->get_wsa_buf(), 1, 
	//						  (LPDWORD)&_recv_buf->get_total_recv(), &flag, 
	//						  (LPWSAOVERLAPPED)_recv_buf, nullptr);
	//	if (SOCKET_ERROR == result)
	//	{
	//		record_error();
	//		return ERR_SOCKET_RECV;
	//	}

	//	return ERR_SUCCEEDED;
	//}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32 SocketAsync::create(const SOCKET & socket_in)
	{
		_tcp_socket = socket_in;

		_recv_buf = new Overlapped();
		_send_buf = new Overlapped();
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32 SocketAsync::recv_async(PacketBuffer* buffer_in)
	{
		_recv_buf->set_type(EOTYPE_RECV);

		DWORD flag = 0;
		DWORD transferred_bytes = 0;
		INT32 result = WSARecv(_tcp_socket, (LPWSABUF)buffer_in, 1,
			&transferred_bytes, &flag,
			(LPWSAOVERLAPPED)_recv_buf, nullptr);
		if (SOCKET_ERROR == result)
		{
			record_error();
			if (WSA_IO_PENDING != get_last_error())
				return ERR_SOCKET_RECV;
		}

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32 SocketAsync::send_async(const PacketBuffer* buffer_in)
	{
		_recv_buf->set_type(EOTYPE_SEND);

		DWORD flag = 0;
		DWORD transferred_bytes = 0;
		INT32 result = WSASend(_tcp_socket, (LPWSABUF)buffer_in, 1,
			&transferred_bytes, flag,
			(LPWSAOVERLAPPED)_recv_buf, nullptr);
		if (SOCKET_ERROR == result)
		{
			record_error();
			if (WSA_IO_PENDING != get_last_error())
				return ERR_SOCKET_RECV;
		}

		return ERR_SUCCEEDED;
	}
}