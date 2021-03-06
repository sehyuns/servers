// @file	overlapped.h
//
//

#ifndef _OVERLAPPED_H_
#define _OVERLAPPED_H_

#pragma once

#include <winsock2.h>


namespace lib
{
	enum EOVERLAP_TYPE
	{
		  EOTYPE_READY
		, EOTYPE_ACCEPT
		, EOTYPE_RECV
		, EOTYPE_SEND
		, EOTYPE_SHUTDOWN
	};


	////////////////////////////////////////////////////////////////////////////////
	// @class	Overlapped
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class Overlapped : public WSAOVERLAPPED
	{
	public:
		Overlapped(INT32 buf_len_in=1024) : _type(EOTYPE_READY)/*, _buffer(nullptr), _buffer_length(buf_len_in)*/, _total_sent(0), _total_recv(0)
		{
			memset(this, 0, sizeof(OVERLAPPED));
			//_buffer = new BYTE[buf_len_in];
			//memset(_buffer, 0, sizeof(buf_len_in));
			//_wsa_buf.buf = (CHAR*)_buffer;
			//_wsa_buf.len = _buffer_length = buf_len_in;
		}

		~Overlapped()
		{
			//if (nullptr != _buffer)
			//	delete _buffer;
			//_buffer = nullptr;
		}

		VOID		reset(VOID)
		{
			memset(this, 0, sizeof(OVERLAPPED));
			//_buffer[0] = '\0';
		}

	public:
		VOID		set_type(INT32 type_in)				{ _type = type_in; }
		INT32		get_type(VOID)						{ return _type; }

		//WSABUF*		get_wsa_buf(VOID)					{ return &_wsa_buf; }
		INT32&		get_total_recv(VOID)				{ return _total_recv; }
		INT32&		get_total_sent(VOID)				{ return _total_sent; }

		//VOID		set_buffer(const BYTE* buffer_in, INT32 length_in)
		//{
		//	memcpy(_buffer, buffer_in, length_in);
		//	_wsa_buf.len = length_in;
		//}

	private:
		INT32		_type;

		//WSABUF		_wsa_buf;
		//BYTE*		_buffer;
		//INT32		_buffer_length;

		INT32		_total_sent;
		INT32		_total_recv;
	};
}

#endif
