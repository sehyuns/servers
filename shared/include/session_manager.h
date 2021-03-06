// @file	session_manager.h
//
//

#ifndef _SESSION_MANAGER_H_
#define _SESSION_MANAGER_H_

#pragma once

#include "shared_defs.h"
#include "singleton.h"

#include <unordered_map>

namespace shared
{
	class Session;
}

namespace shared
{
	////////////////////////////////////////////////////////////////////////////////
	// @class
	//
	// @brief
	//			
	////////////////////////////////////////////////////////////////////////////////
	class SessionManager : public lib::Singleton<SessionManager>
	{
	public:
		SessionManager();
		~SessionManager();

	public:
		Session*	create_session(INT32 key_in, const SOCKET& socket_in);
		INT32		add_session(INT32 key_in, Session* session_in);
		INT32		close_session(INT32 key_in);

		Session*	get_session(INT32 key_in);

	private:
		typedef		std::unordered_map<INT32, Session*>	TSessionMap;
		TSessionMap		_session_map;
	};

}

#endif
