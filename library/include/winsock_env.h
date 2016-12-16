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
	// @brief	Windows socket�� ����ϱ� ���ؼ� ���Ǵ� ȯ�� ����
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