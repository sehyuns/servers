// @file	base_acceptor.cpp
//
//

#include "base_acceptor.h"
#include "session_manager.h"
#include "session.h"
#include "iocp.h"

#include "socket_async.h"

#include <mswsock.h>

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
	INT32	BaseAcceptor::initialize(const string& address_in, SHORT port, lib::Iocp* iocp_in, INT32 sock_num_in)
	{
		//_iocp = new lib::Iocp();

		//INT32 result = _iocp->initialize();
		//if (ERR_SUCCEEDED != result)
		//{
		//	return result;
		//}

		_iocp = iocp_in;

		_acceptor = new lib::SocketAsync();

		if (FALSE == _acceptor->init_address(address_in, port))
		{
			return ERR_SOCKET_ADDRESS;
		}

		INT32 result = _acceptor->init_server();
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		//result = initialize();
		//if (ERR_SUCCEEDED != result)
		//{
		//	return result;
		//}

		//result = register_thread(string("acceptor"), &BaseAcceptor::acceptor_thread);
		//if (ERR_SUCCEEDED != result)
		//{
		//	return result;
		//}
		
		result = register_thread(string("acceptor_worker"), &BaseAcceptor::worker_thread);
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}		

		result = _iocp->create_new_session(_acceptor->get_socket());
		if (ERR_SUCCEEDED != result)
		{
			return result;
		}

		LPFN_ACCEPTEX acceptex_func = nullptr;
		GUID guid_acceptex = WSAID_ACCEPTEX;
		DWORD bytes = 0;

		if (SOCKET_ERROR == WSAIoctl(_acceptor->get_socket(), SIO_GET_EXTENSION_FUNCTION_POINTER,
							&guid_acceptex, sizeof(guid_acceptex),
							&acceptex_func, sizeof(acceptex_func),
							&bytes, nullptr, nullptr))
		{
			return ERR_SOCKET_ACCEPT;
		}
		
		char lpOutputBuf[1024];
		int outBufLen = 1024;
		OVERLAPPED overlapped;

		for (INT32 ii = 0; ii < sock_num_in; ++ii)
		{
			SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			memset(&overlapped, 0, sizeof(overlapped));

			if (FALSE == acceptex_func(_acceptor->get_socket(), client_socket, lpOutputBuf, outBufLen - ((sizeof(sockaddr_in) + 16) * 2), sizeof(sockaddr_in) + 16, sizeof(sockaddr_in) + 16, &bytes, &overlapped))
			{
				INT32 err_code = WSAGetLastError();
				if (WSA_IO_PENDING != err_code)
				{
					return ERR_SOCKET_ACCEPT;
				}
			}

			_iocp->create_new_session(client_socket);
		}
		
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

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	BaseAcceptor::worker_thread()
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
}