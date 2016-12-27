// @file	base_acceptor.h
//
//

#ifndef	_BASE_ACCEPTOR_H_
#define _BASE_ACCEPTOR_H_

#pragma once

#include "shared_defs.h"

#include "thread.h"
#include "winsock_env.h"


namespace lib
{
	class Iocp;
	class SocketAsync;
}

namespace shared
{
	////////////////////////////////////////////////////////////////////////////////
	// @class	BaseAcceptor
	//
	// @brief	IOCP를 활용한 acceptor로서 새로운 connection을 비동기로 기다리며, connection 요청에 응답한다.
	//			
	////////////////////////////////////////////////////////////////////////////////
	class BaseAcceptor : public lib::Thread, public lib::WinsockEnv
	{
	public:
		BaseAcceptor();
		~BaseAcceptor();

	public:
		INT32		initialize(const string& address_in, SHORT port);
		VOID		close();

		virtual INT32	worker_thread() override;

	private:
		lib::Iocp*				_iocp;
		lib::SocketAsync*		_acceptor;
	};
}

#endif
