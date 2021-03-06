// @file	connector_defs.h
//
//

#ifndef _CONNECTOR_DEFS_H_
#define _CONNECTOR_DEFS_H_

#pragma once

#include "shared_defs.h"


#ifdef SHARED_CONNECTOR_EXPORTS
	#define DLL_ENTRY		__declspec(dllexport)
#else
	#define DLL_ENTRY		__declspec(dllimport)
#endif

#endif
