// @file	base_acceptor.cpp
//
//

#include "base_acceptor.h"
#include "session_manager.h"
#include "session.h"
#include "iocp.h"

#include "socket_async.h"

namespace shared
{

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	BaseAcceptor::BaseAcceptor()
		: _acceptor(nullptr)
		, _iocp(nullptr)
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	BaseAcceptor::~BaseAcceptor()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	BaseAcceptor::initialize(const string& address_in, SHORT port)
	{
		_iocp = new lib::Iocp();

		INT32 result = _iocp->initialize();
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		_acceptor = new lib::SocketAsync();

		if (FALSE == _acceptor->init_address(address_in, port))
		{
			return ERR_SOCKET_ADDRESS;
		}

		result = _acceptor->init_server();
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		//result = initialize();
		//if (ERR_SUCCEEDED != result)
		//{
		//	return result;
		//}

		result = register_thread(string("acceptor"), &BaseAcceptor::acceptor_thread);
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		result = register_thread(string("acceptor_worker"), &BaseAcceptor::worker_thread);
		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	BaseAcceptor::close()
	{
		// make temporary socket for close
		if (nullptr != _iocp)
		{
			_iocp->close();
			delete _iocp;
		}

		if (nullptr != _acceptor)
		{
			_acceptor->close();
			delete _acceptor;
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	BaseAcceptor::acceptor_thread()
	{
		while (TRUE)
		{
			SOCKET client_socket = _acceptor->accept();
			if (INVALID_SOCKET == client_socket)
			{
				return ERR_SOCKET_ACCEPT;
			}

			Session* session = SessionManager::get_instance()->create_session((INT)client_socket, client_socket);
			if (nullptr == session)
			{
				printf("Failed to make new session!!\n");
				continue;
			}

			printf("accepted new client connection!!(%d)\n", (INT32)client_socket);

			INT32 result = _iocp->create_new_session(client_socket);
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to combine with iocp!!\n");
				continue;
			}

			// make packet
			// move or copy packet to other place. 

			session->send((BYTE*)"hello", 6);

			// reset
			result = session->recv();
			if (ERR_SUCCEEDED != result)
			{
				printf("Failed to recv !!\n");
				continue;
			}
		}
		return ERR_SUCCEEDED;
	}
}