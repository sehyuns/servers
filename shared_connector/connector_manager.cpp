// @file	connector_manager.cpp
//
//

#include "connector_manager.h"
#include "connector.h"

#include "iocp.h"

#include <process.h>

namespace connector
{
	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	unsigned __stdcall main_worker_thread(void* argument)
	{
		return  ConnectorManager::get_instance()->worker_thread();
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	ConnectorManager::ConnectorManager() 
		: _close_event(nullptr), _is_continue(FALSE),
		  _iocp(nullptr),
		  _session_connector(nullptr)
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	ConnectorManager::~ConnectorManager()
	{

	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	ConnectorManager::initialize(string& address_in, SHORT port_in)
	{
		_iocp = new lib::Iocp();

		INT32 result = _iocp->initialize();
		if (ERR_SUCCEEDED != result)
			return result;

		_session_connector = new Connector();

		result = _iocp->create_new_session(*_session_connector);
		if (ERR_SUCCEEDED != result)
			return result;

		_is_continue = TRUE;
		HANDLE event = CreateEvent(nullptr, TRUE, FALSE, TEXT("close_event"));
		if (INVALID_HANDLE_VALUE == event)
		{
			return FALSE;
		}
		_close_event = (VOID*)event;

		_beginthreadex(nullptr, 0, &main_worker_thread, this, 0, nullptr);

		return TRUE;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	ConnectorManager::close()
	{
		WaitForSingleObject((HANDLE)_close_event, INFINITE);

		if (nullptr != _iocp)
			delete _iocp;
		_iocp = nullptr;

		CloseHandle(_close_event);

		if (nullptr != _session_connector)
			delete _session_connector;
		_session_connector = nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	INT32	ConnectorManager::worker_thread()
	{
		while (_is_continue)
		{
			INT32 key = 0;
			UINT32 transferred_bytes = 0;
			LPOVERLAPPED overlapped = nullptr;

			INT32 result = _iocp->pop_income(key, transferred_bytes, overlapped);
			if (ERR_SUCCEEDED != result)
			{
				continue;
			}

			// process income packet
		}

		ResetEvent((HANDLE)_close_event);
		return 0;
	}
}