//
//
//


#ifndef _DEFS_H_
#define _DEFS_H_

#pragma once

#include <string>
#include <tchar.h>
#include <stdlib.h>

#include <winsock2.h>


using namespace std;


typedef	std::basic_string<TCHAR>	tstring;



//inline void		make_error_string(INT32 err_in)
//{
//	TCHAR* error_string = nullptr;
//	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
//		NULL, err_in, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//		(LPTSTR)&error_string, 0, NULL);
//
//	LocalFree(error_string);
//}

#endif
