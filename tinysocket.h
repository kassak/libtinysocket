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
#elif defined(TINYSOCKET_BSDSOCK)
   #include <sys/types.h>
   #include <sys/socket.h>
   #include <arpa/inet.h>
   #include <netinet/in.h>
   #include <poll.h>
   #include <unistd.h>
   #include <errno.h>
   #include <fcntl.h>
#else
   #error "oups"
#endif

#ifndef TINYSOCKET_USER_PREFIX
   #define TINYSOCKET_PREFIX tinsock_
#else
   #define TINYSOCKET_PREFIX TINYSOCKET_USER_PREFIX
#endif

#define TINYSOCKET_CONCAT2(X, Y) X##Y
#define TINYSOCKET_CONCAT(X, Y) TINYSOCKET_CONCAT2(X, Y)
#define TINYSOCKET_ITEM(X)  TINYSOCKET_CONCAT(TINYSOCKET_PREFIX, X)
#define TINYSOCKET_FUNCTION(RET, FOO) static inline RET TINYSOCKET_ITEM(FOO)
#define TINYSOCKET_NO_REALISATION char[-1] a
// In C there must be prefix in C++ there must be namespace
// that is why native is called from global scope
#ifndef __cplusplus
   #define TINYSOCKET_NATIVE_ACCESS
#else
   #define TINYSOCKET_NATIVE_ACCESS ::
#endif

// ==== TYPES ====
#include "tinysocket/tinytypes.h"

// ==== CONSTANTS ====
#include "tinysocket/tinybits.h"

// ==== FUNCTIONS ====
#include "tinysocket/tinysocketmanip.h"
#include "tinysocket/tinyaddress.h"
#include "tinysocket/tinyutils.h"

//CUSTOM
TINYSOCKET_FUNCTION(int, is_recoverable)()
{
   return TINYSOCKET_ITEM(last_error)() == TS_EWOULDBLOCK
       || TINYSOCKET_ITEM(last_error)() == TS_EAGAIN;
}

TINYSOCKET_FUNCTION(int, v4v6_inet_pton)(const char * s, TINYSOCKET_ITEM(sockaddr_storage_t) * stor)
{
   if(1 == tinsock_inet_pton(TS_AF_INET6, s, &((TINYSOCKET_ITEM(sockaddr_in6_t)*)stor)->sin6_addr))
   {
      stor->ss_family = TS_AF_INET6;
   }
   else if(1 == tinsock_inet_pton(TS_AF_INET, s, &((TINYSOCKET_ITEM(sockaddr_in_t)*)stor)->sin_addr))
   {
      stor->ss_family = TS_AF_INET;
   }
   else
      return 0;
   return 1;
}

TINYSOCKET_FUNCTION(void, v4v6_set_port)(TINYSOCKET_ITEM(sockaddr_storage_t) * stor, uint16_t port)
{
   if(stor->ss_family == TS_AF_INET6)
      ((TINYSOCKET_ITEM(sockaddr_in6_t)*)stor)->sin6_port = port;
   else if(stor->ss_family == TS_AF_INET)
      ((TINYSOCKET_ITEM(sockaddr_in_t)*)stor)->sin_port = port;
}

#undef TINYSOCKET_PREFIX
#undef TINYSOCKET_CONCAT
#undef TINYSOCKET_CONCAT2
#undef TINYSOCKET_ITEM
#undef TINYSOCKET_FUNCTION
#undef TINYSOCKET_NATIVE_CALL
#undef TINYSOCKET_NO_REALISATION

#endif //TINYSOCKET_H
