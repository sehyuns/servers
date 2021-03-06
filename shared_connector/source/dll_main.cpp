// @file	dll_main.cpp
//
//

#include "connector_defs.h"

#include "connector_manager.h"


DLL_ENTRY BOOL	initialize(string& address_in, SHORT port_in);
DLL_ENTRY VOID	close();

BOOL APIENTRY DllMain(_In_ void* _DllHandle, _In_ unsigned long _Reason, _In_opt_ void* _Reserved)
{
	return TRUE;
}


DLL_ENTRY BOOL	initialize(string& address_in, SHORT port_in)
{
	connector::ConnectorManager::get_instance();

	INT32 result = connector::ConnectorManager::get_instance()->initialize(address_in, port_in);
	if (ERR_SUCCEEDED != result)
		return FALSE;

	return TRUE;
}

DLL_ENTRY VOID	close()
{
	connector::ConnectorManager::get_instance()->close();
}
