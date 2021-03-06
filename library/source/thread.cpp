// @file	thread.cpp
//
//
//
//#include "thread.h"
//
//#include "error_defs.h"
//
//#include <process.h>
//

namespace lib
{
	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//Thread<T>::Thread()
	//	: _thread_handle(INVALID_HANDLE_VALUE)
	//{

	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//Thread<T>::~Thread()
	//{

	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//INT32	Thread<T>::initialize()
	//{
	//	//_thread_handle = (HANDLE)_beginthreadex(nullptr, 0, &main_thread, this, CREATE_SUSPENDED, nullptr);
	//	//if (INVALID_HANDLE_VALUE == _thread_handle)
	//	//{
	//	//	return ERR_THREAD_CREATE_THREAD;
	//	//}

	//	return ERR_SUCCEEDED;
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//VOID	Thread<T>::close()
	//{
	//	WaitForSingleObject(_thread_handle, INFINITE);

	//	CloseHandle(_thread_handle);
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//INT32	Thread<T>::register_thread(const string& name_in, ThreadFunc func_in, SHORT thread_num_in)
	//{
	//	THandleMap::iterator iter = _handle_map.find(name_in);
	//	if (iter != _handle_map.end())
	//		return ERR_THREAD_CREATE_THREAD;

	//	std::pair<TArgumentMap::iterator, bool> arg_result = _argument_map.insert(TArgumentMap::value_type(name_in, ThreadArg(this, name_in)));
	//	if (false == arg_result.second)
	//	{
	//		return ERR_THREAD_CREATE_THREAD;
	//	}

	//	std::pair<TFuncMap::iterator, bool> func_result = _func_map.insert(TFuncMap::value_type(name_in, func_in));
	//	if (false == func_result.second)
	//	{
	//		return ERR_THREAD_CREATE_THREAD;
	//	}

	//	THandleList handle_list;
	//	HANDLE thread_handle = INVALID_HANDLE_VALUE;
	//	for (INT32 ii = 0; ii < thread_num_in; ++ii)
	//	{
	//		thread_handle = (HANDLE)_beginthreadex(nullptr, 0, &main_thread, &(arg_result.first->second), CREATE_SUSPENDED, nullptr);
	//		handle_list.push_back(thread_handle);
	//	}

	//	_handle_map.insert(THandleMap::value_type(name_in, handle_list));

	//	return ERR_SUCCEEDED;
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//INT32	Thread<T>::start_all_threads()
	//{
	//	for (auto& iter_ii : _handle_map)
	//	{
	//		for (auto& iter_jj : iter_ii->second)
	//		{
	//			ResumeThread(*iter_jj);
	//		}
	//	}		

	//	return ERR_SUCCEEDED;
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//INT32	Thread<T>::stop_all_threads()
	//{
	//	_endthreadex(0);
	//	return ERR_SUCCEEDED;
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//unsigned Thread<T>::thread_main(void * argument)
	//{
	//	ThreadArg* thread_arg = (ThreadArg*)argument;
	//	Thread* thread = (Thread*)thread_arg->_object;
	//	return thread->run_thread(thread_arg->_name);
	//}

	//////////////////////////////////////////////////////////////////////////////////
	////
	//////////////////////////////////////////////////////////////////////////////////
	//template<typename T>
	//INT32 Thread<T>::run_thread(const string & name_in)
	//{
	//	TFuncMap::iterator iter = _func_map.find(name_in);
	//	if (iter == _func_map.end())
	//		return -1;

	//	T temp;
	//	return (temp.*(iter->second))();
	//}
}