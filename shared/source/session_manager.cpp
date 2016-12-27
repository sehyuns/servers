// @file	session_manager.cpp
//
//

#include "session_manager.h"

#include "session.h"

namespace shared
{
	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SessionManager::SessionManager()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SessionManager::~SessionManager()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	Session*	SessionManager::create_session(INT32 key_in, const SOCKET& socket_in)
	{
		Session* session = new Session();
		INT32 result = session->initialize(socket_in);
		if (ERR_SUCCEEDED != result)
			return nullptr;

		_session_map.insert(TSessionMap::value_type((INT32)socket_in, session));

		return session;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SessionManager::add_session(INT32 key_in, Session* session_in)
	{
		_session_map.insert(TSessionMap::value_type(key_in, session_in));
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SessionManager::close_session(INT32 key_in)
	{
		TSessionMap::iterator it = _session_map.find(key_in);
		if (_session_map.end() == it)
			return ERR_SHARED_SESSION_FIND;

		delete it->second;
		_session_map.erase(key_in);

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	Session * SessionManager::get_session(INT32 key_in)
	{
		TSessionMap::iterator iter = _session_map.find(key_in);
		if (_session_map.end() == iter)
			return nullptr;

		return iter->second;
	}

}
