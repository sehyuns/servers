
#include "socket.h"
#include "error_defs.h"

#include "base_connector.h"
#include "session_manager.h"

using namespace lib;

int main(void)
{
	WSADATA wsa_data;

	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	shared::SessionManager::create();

	shared::BaseConnector connector;

	INT32 result = connector.initialize();
	if (ERR_SUCCEEDED != result)
		exit(1);

	connector.start_all_threads();

	result = connector.add_connection(string("127.0.0.1"), 8010);
	if (ERR_SUCCEEDED != result)
		exit(2);

	printf("succeeded to connect to server!!\n");

	while(true)
	{ }

	//Socket client;

	//if (FALSE == client.init_address(string("127.0.0.1"), 8010))
	//{
	//	exit(1);
	//}

	//INT32 result = client.start_client();
	//if (ERR_SUCCEEDED != result)
	//{
	//	exit(result);
	//}

	//CHAR buffer[1024] = { 0, };
	//INT32 length = 1024;

	//strcpy_s(buffer, 12, "hello world");

	//result = client.send((BYTE*)&buffer, 13);
	//if (ERR_SUCCEEDED != result)
	//{
	//	exit(result);
	//}
	//result = client.recv((BYTE*)&buffer, length);
	//if (ERR_SUCCEEDED != result)
	//{
	//	exit(result);
	//}

	WSACleanup();
	return 0;
}