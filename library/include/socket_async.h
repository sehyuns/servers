// @file	socket_async.h
//
//

#ifndef _SOCKET_ASYNC_H_
#define _SOCKET_ASYNC_H_

#pragma once

#include "socket.h"

namespace lib
{
	class Overlapped;
	class PacketBuffer;
}


namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	SocketAsync
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class SocketAsync : public Socket
	{
	private:
		typedef	Socket	Super;

	public:
		SocketAsync();
		~SocketAsync();

	public:
		virtual INT32	create() override;
		virtual VOID	close() override;

		virtual SOCKET	accept() override;
		virtual INT32	connect() override;

		//virtual INT32	send(const BYTE* buffer_in, INT32 length_in) override;
		//virtual INT32	recv(const BYTE* buffer_out, INT32& length_out) override;

	public:
		INT32			create(const SOCKET& socket_in);

		INT32			recv_async(PacketBuffer* buffer_in);
		INT32			send_async(const PacketBuffer* buffer_in);

	private:
		Overlapped*			_recv_buf;
		Overlapped*			_send_buf;
	};
}

#endif
