
#include "socket.h"
#include "error_defs.h"

using namespace lib;

int main(void)
{
	WSADATA wsa_data;

	WSAStartup(MAKEWORD(2, 2), &wsa_data);

	Socket client;

	if (FALSE == client.init_address(string("127.0.0.1"), 8010))
	{
		exit(1);
	}

	INT32 result = client.start_client();
	if (ERR_SUCCEEDED != result)
	{
		exit(result);
	}

	CHAR buffer[1024] = { 0, };
	INT32 length = 1024;

	strcpy_s(buffer, 12, "hello world");

	result = client.send((BYTE*)&buffer, 13);
	if (ERR_SUCCEEDED != result)
	{
		exit(result);
	}
	result = client.recv((BYTE*)&buffer, length);
	if (ERR_SUCCEEDED != result)
	{
		exit(result);
	}

	WSACleanup();
	return 0;
}