// @file	base_connector.cpp
//
//

#include "base_connector.h"
#include "session_manager.h"
#include "session.h"

#include "iocp.h"

namespace shared
{
	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	BaseConnector::BaseConnector()
		: _iocp(nullptr)
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	BaseConnector::~BaseConnector()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	BaseConnector::initialize()
	{
		_iocp = new lib::Iocp();

		INT32 result = _iocp->initialize();
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		//result = initialize();
		//if (ERR_SUCCEEDED != result)
		//{
		//	return result;
		//}

		result = register_thread(string("connector_worker"), &BaseConnector::worker_thread);
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	BaseConnector::close()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	BaseConnector::worker_thread()
	{
		INT32 result = ERR_SUCCEEDED;

		while (TRUE)
		{
			INT32 key = 0;
			UINT32 transferred_bytes = 0;
			LPOVERLAPPED overlapped = nullptr;
			result = _iocp->pop_income(key, transferred_bytes, &overlapped);
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to get income(%d)\n", key);
				continue;
			}

			Session* session = SessionManager::get_instance()->get_session(key);
			if (nullptr == session)
			{
				printf("Failed to find session(%d)\n", key);
				continue;
			}

			// make packet
			// move or copy packet to other place.

			// reset
			result = session->recv();
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to recv(%d) !!\n", result);
				continue;
			}
		}
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	BaseConnector::add_connection(const string& address_in, SHORT port)
	{
		Session* session = new Session();

		lib::SocketAsync* socket = session->get_socket();
		INT32 result = socket->create();
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		if (FALSE == socket->init_address(address_in, port))
		{
			return result;
		}

		result = _iocp->create_new_session(socket->get_socket());
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		result = socket->connect();
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		SessionManager::get_instance()->add_session((INT32)socket->get_socket(), session);

		session->recv();

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
}