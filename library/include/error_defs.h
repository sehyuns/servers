// @file	error_defs.h
//
//

#ifndef _ERROR_DEFS_H_
#define ERROR_DEFS_H_

#pragma once


enum ERROR_LIBRARY
{
	  ERR_SUCCEEDED = 0
	, ERR_SOCKET_MAKE
	, ERR_SOCKET_ADDRESS
	, ERR_SOCKET_BIND
	, ERR_SOCKET_LISTEN
	, ERR_SOCKET_ACCEPT
	, ERR_SOCKET_CONNECT
	, ERR_SOCKET_OPTION
	, ERR_SOCKET_IOCTL
	, ERR_SOCKET_SEND
	, ERR_SOCKET_RECV

	, ERR_IOCP_CREATE = 100
	, ERR_IOCP_NEW
	, ERR_IOCP_QUEUE
	, ERR_IOCP_POST
};

#endif