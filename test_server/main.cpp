

#include "shared_server.h"

//#include "socket_async.h"
//#include "iocp.h"
//
//#include "error_defs.h"
#include <WS2tcpip.h>
#include <process.h>



#include "base_acceptor.h"
#include "session_manager.h"
#include "iocp.h"

int main()
{
	WSADATA wsa_data;
	
	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	//shared::SharedServer server;

	//INT32 result = server.initialise(string("0.0.0.0"), 8010);
	//if (ERR_SUCCEEDED != result)
	//	exit(result);

	//server.start();

	shared::SessionManager::create();

	lib::Iocp iocp;
	iocp.initialize();

	shared::BaseAcceptor acceptor;

	INT32 result = acceptor.initialize(string("0.0.0.0"), 8010, &iocp, 10);
	if (ERR_SUCCEEDED != result)
		exit(1);

	result = acceptor.start_all_threads();
	if (ERR_SUCCEEDED != result)
		exit(2);

	//MainThread thread;
	//thread.init();

	//thread.start_thread();

	while (true)
	{
	}

//	WSADATA wsa_data;
//
//	WSAStartup(MAKEWORD(2, 2), &wsa_data);
//
//#if 0
//	Socket server;
//
//	if (FALSE == server.init_address(string("0.0.0.0"), 8010))
//	{
//		exit(1);
//	}
//
//	INT32 result = server.init_server();
//	if (ERR_SUCCEEDED != result)
//	{
//		exit(result);
//	}
//
//	Socket client;
//
//	result = server.accept(&client);
//	if (ERR_SUCCEEDED != result)
//	{
//		exit(result);
//	}
//
//	printf("connected new client!!!!\n");
//
//	CHAR buffer[1024] = { 0, };
//	INT32 length = 1024;
//
//	result = client.recv((BYTE*)&buffer, length);
//	if (ERR_SUCCEEDED != result)
//	{
//		exit(result);
//	}
//
//	result = client.send((BYTE*)&buffer, length);
//	if (ERR_SUCCEEDED != result)
//	{
//		exit(result);
//	}
//#else
//
//	SocketAsync server;
//
//	if (FALSE == server.init_address(string("0.0.0.0"), 8010))
//		exit(1);
//
//	INT32 result = server.init_server();
//	if (ERR_SUCCEEDED != result)
//		exit(result);
//
//	Iocp iocp;
//	result = iocp.initialize();
//	if (ERR_SUCCEEDED != result)
//		exit(result);
//
//	// create iocp thread
//	_beginthreadex(nullptr, 1024, worker_thread, &iocp, 0, nullptr);
//
//	SocketAsync client;
//
//	result = client.create();
//	if (ERR_SUCCEEDED != result)
//		exit(result);
//
//	printf("create client socket(%d)\n", (INT32)client.get_socket());
//
//	while (TRUE)
//	{
//		result = server.accept(&client);
//		if (ERR_SUCCEEDED != result)
//			exit(result);
//
//		printf("accept client socket(%d)\n", (INT32)client.get_socket());
//
//		// bind with iocp
//		result = iocp.create_new_session(&client);
//		if (ERR_SUCCEEDED != result)
//			exit(result);
//
//		int length = 0;
//		result = client.recv(nullptr, length);
//		if (ERR_SUCCEEDED != result)
//			exit(result);
//	}
//
//#endif
//
//	WSACleanup();


	return 0;
}
//
//unsigned __stdcall worker_thread(void* argument)
//{
//	Iocp* iocp = (Iocp*)argument;
//
//	while (TRUE)
//	{
//		INT32 key = 0;
//		UINT32 transferred_bytes = 0;
//		LPOVERLAPPED overlapped = nullptr;
//		INT32 result = iocp->pop_income(key, transferred_bytes, overlapped);
//		if (ERR_SUCCEEDED != result)
//			exit(result);
//
//		printf("pop income(key: %d)!!", key);
//		// find key
//		// check status
//	}
//	return 0;
//}
