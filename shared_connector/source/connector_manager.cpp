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
		return ConnectorManager::get_instance()->worker_thread();
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	ConnectorManager::ConnectorManager() 
		: _session_connector(nullptr)
		, _is_continue(FALSE)
		, _close_event(INVALID_HANDLE_VALUE)
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

		result = _session_connector->initialize(address_in, port_in);
		if (ERR_SUCCEEDED != result)
			return result;

		_iocp->create_new_session(*_session_connector);

		_is_continue = TRUE;
		_close_event = CreateEvent(nullptr, FALSE, FALSE, TEXT("shared_close_event"));

		_beginthreadex(nullptr, 0, &main_worker_thread, this, 0, nullptr);

		return ERR_SUCCEEDED;
	}

	////////////////////////////////////////////////////////////////////////////////
	//
	////////////////////////////////////////////////////////////////////////////////
	VOID	ConnectorManager::close()
	{
		_is_continue = FALSE;

		WaitForSingleObject(_close_event, INFINITE);

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

			// process incoming packet
		}

		ResetEvent((HANDLE)_close_event);

		return ERR_SUCCEEDED;
	}
}