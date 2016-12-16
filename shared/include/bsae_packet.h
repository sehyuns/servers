// @file	base_packet.h
//
//

#ifndef _BASE_PACKET_H_
#define _BASE_PACKET_H_

#pragma once

namespace shared
{
#pragma pack(push, 1)
	////////////////////////////////////////////////////////////////////////////////
	// @class	BasePacket
	//
	// @brief	Network packet의 기본이 되며, 암호화 및 공용으로 사용되는 모듈을 적재하고 있다.
	//			
	////////////////////////////////////////////////////////////////////////////////
	class BasePacket
	{
	public:
		BasePacket()
		{

		}

		~BasePacket()
		{

		}
	};

#pragma pack(pop)
}

#endif
