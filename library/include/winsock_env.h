// @file	winsock_env.h
//
//

#ifndef _WINSOCK_ENV_H_
#define _WINSOCK_ENV_H_

#pragma once


namespace lib
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	WinsockEnv
	//
	// @brief	Windows socket을 사용하기 위해서 사용되는 환경 설정
	//			
	////////////////////////////////////////////////////////////////////////////////
	class WinsockEnv
	{
	public:
		WinsockEnv();
		~WinsockEnv();

	private:
		void*		_wsa_data;
	};
}

#endif