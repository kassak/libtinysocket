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
   #include <errno.h>
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

// ==== CONSTANTS ====
#include "tinysocket/tinybits.h"

// ==== TYPES ====
#include "tinysocket/tinytypes.h"

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


#undef TINYSOCKET_PREFIX
#undef TINYSOCKET_CONCAT
#undef TINYSOCKET_CONCAT2
#undef TINYSOCKET_ITEM
#undef TINYSOCKET_FUNCTION
#undef TINYSOCKET_NATIVE_CALL
#undef TINYSOCKET_NO_REALISATION

#endif //TINYSOCKET_H
