#pragma once

#define _MAC_OS_		( __APPLE__ | __MACH__ )
#if (!_MAC_OS_)
#define _LINUX_OS_		( __linux__ | linux | __linux )
#if (!_LINUX_OS_)
#define _WINDOWS_OS_	( _WIN32 | _WIN64 )	
#endif
#endif

#if _LINUX_OS_
#include <stdio.h> 
#include <stdlib.h> 
#include <cstdio>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <chrono>
#include <unistd.h>
#include <arpa/inet.h>
#else
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<stdio.h>
#pragma comment(lib, "Ws2_32.lib")
#include <process.h>
#include <windows.h>
#endif


#if _LINUX_OS_
#define Sleep(mSec)											usleep((mSec*1000))
#define closesocket(_Sckt_)									close(_Sckt_)

#endif
