// @file	packet_buffer.h
//
//

#ifndef _PACKET_BUFFER_H_
#define _PACKET_BUFFER_H_

#pragma once

#include "winsock2.h"


namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	PacketBuffer
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class PacketBuffer : public WSABUF
	{
	public:
		PacketBuffer(INT32 length_in) : _buffer(nullptr)
		{
			_buffer = new BYTE[length_in];
			memset(_buffer, 0, length_in);
			buf = (CHAR*)_buffer;
			len = length_in;
			_length = length_in;
		}

		~PacketBuffer()
		{
			if (nullptr != _buffer)
				delete _buffer;
			_buffer = nullptr;
		}

		VOID		reset(VOID)
		{
			memset(_buffer, 0, _length);
			len = _length;
		}

	private:
		BYTE*		_buffer;
		INT32		_length;
	};
}

#endif
