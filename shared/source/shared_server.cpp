// @file	shared_server.cpp
//
//

#include "shared_server.h"
#include "session_manager.h"
#include "session.h"

#include "socket_async.h"
#include "iocp.h"
#include "overlapped.h"

#include <process.h>

namespace shared
{

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	unsigned __stdcall main_acceptor_thread(void* argument_in)
	{
		SharedServer* server = (SharedServer*)argument_in;
		INT32 result = server->acceptor_thread();

		return result;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	unsigned __stdcall main_worker_thread(void* argument_in)
	{
		SharedServer* server = (SharedServer*)argument_in;
		INT32 result = server->worker_thread();

		return result;
	}



	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SharedServer::SharedServer() : _iocp(nullptr), _listen_socket(nullptr)
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	SharedServer::~SharedServer()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SharedServer::initialise(const string& address_in, SHORT port_in)
	{
		_listen_socket = new lib::SocketAsync();

		if (FALSE == _listen_socket->init_address(address_in, port_in))
			return ERR_SOCKET_ADDRESS;
		
		INT32 result = _listen_socket->init_server();
		if (ERR_SUCCEEDED != result)
			return result;

		_iocp = new lib::Iocp();

		result = _iocp->initialize();
		if (ERR_SUCCEEDED != result)
			return result;

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	SharedServer::close()
	{
		if (nullptr != _iocp)
		{
			_iocp->close();
			delete _iocp;
		}

		if (nullptr != _listen_socket)
		{
			_listen_socket->close();
			delete _listen_socket;
		}

		_iocp = nullptr;
		_listen_socket = nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SharedServer::start()
	{
		_beginthreadex(nullptr, 0, &main_acceptor_thread, this, 0, nullptr);

		_beginthreadex(nullptr, 0, &main_worker_thread, this, 0, nullptr);

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SharedServer::acceptor_thread()
	{
		while (TRUE)
		{
			SOCKET client_socket = _listen_socket->accept();
			if (INVALID_SOCKET == client_socket)
			{
				printf("Failed to accept client socket!!\n");
				continue;
			}

			Session* session = SessionManager::get_instance().create_session((INT)client_socket, client_socket);
			if (nullptr == session)
			{
				printf("Failed to make new session!!\n");
				continue;
			}

			INT32 result = _iocp->create_new_session(client_socket);
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to combine with iocp!!\n");
				continue;
			}

			result = session->recv();
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to recv !!\n");
				continue;
			}

		}
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	SharedServer::worker_thread()
	{
		while (TRUE)
		{
			INT32 key = 0;
			UINT32 transferred_bytes = 0;
			LPOVERLAPPED overlapped = nullptr;

			INT32 result = _iocp->pop_income(key, transferred_bytes, overlapped);
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to pop incomes(%d)\n", result);
				continue;
			}

			Session* session = SessionManager::get_instance().get_session(key);
			if (nullptr == session)
			{
				printf("Failed to find session(%d)\n", key);
				continue;
			}

			result = session->recv();
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to recv(%d) !!\n", result);
				continue;
			}
			
		}
		return ERR_SUCCEEDED;
	}
}