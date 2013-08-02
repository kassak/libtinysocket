#ifndef TINYSOCKET_H
#define TINYSOCKET_H

#if defined(_WIN32) || defined(_WIN64)
   #define TINYSOCKET_WINSOCK
#else
   #define TINYSOCKET_BSDSOCK
#endif

#ifdef TINYSOCKET_WINSOCK
   #include <Winsock2.h>
   #pragma comment(lib, "Ws2_32.lib")
#elseif TINYSOCKET_BSDSOCK
   #include <sys/types.h>
   #include <sys/socket.h>
#endif

#ifndef TINYSOCKET_PREFIX
  #define TINYSOCKET_PREFIX tinsock_
#endif

#define TINYSOCKET_ITEM2(X) TINYSOCKET_PREFIX##X
#define TINYSOCKET_ITEM(X) TINYSOCKET_ITEM2(X) 
#define TINYSOCKET_FUNCTION(RET, FOO) inline RET TINYSOCKET_ITEM(FOO)

typedef
#ifdef TINYSOCKET_WINSOCK
   SOCKET
#elseif TINYSOCKET_BSDSOCK
   int
#endif
   TINYSOCKET_ITEM(socket_t);

TINYSOCKET_FUNCTION(TINYSOCKET_ITEM(socket_t), socket)(int domain, int type, int protocol)
{
  return socket(domain, type, protocol);
}

#undef TINYSOCKET_PREFIX
#undef TINYSOCKET_ITEM2
#undef TINYSOCKET_ITEM

#endif