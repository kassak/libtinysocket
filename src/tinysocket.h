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

#ifndef TINYSOCKET_USER_PREFIX
   #define TINYSOCKET_PREFIX tinsock_
#else
   #define TINYSOCKET_PREFIX TINYSOCKET_USER_PREFIX
#endif

#define TINYSOCKET_CONCAT2(X, Y) X##Y
#define TINYSOCKET_CONCAT(X, Y) TINYSOCKET_CONCAT2(X) 
#define TINYSOCKET_ITEM(X)  TINYSOCKET_CONCAT(TINYSOCKET_PREFIX, X) 
#define TINYSOCKET_FUNCTION(RET, FOO) inline RET TINYSOCKET_ITEM(FOO)
// In C there must be prefix in C++ there must be namespace
// that is why native is called from global scope
#ifdnef __cplusplus
   #define TINYSOCKET_NATIVE_ACCESS
#else
   #define TINYSOCKET_NATIVE_ACCESS ::
#endif

// ==== CONSTANTS ====
#ifdef TINYSOCKET_WINSOCK
enum 
{
  TS_SOCKET_ERROR = SOCKET_ERROR,
 
};

#elseif TINYSOCKET_BSDSOCK
enum 
{
  TS_SOCKET_ERROR = -1,
 
};
#endif

enum poll_events_t
{
#ifdef TINYSOCKET_WINSOCK
   TS_POLLIN   = POLLRDNORM,
   TS_POLLPRI  = POLLPRI, 
   TS_POLLOUT  = POLLWRNORM,
   TS_POLLERR  = POLLERR,
   TS_POLLHUP  = POLLHUP,
   TS_POLLNVAL = POLLNVAL,
#elseif TINYSOCKET_BSDSOCK
   TS_POLLIN   = POLLIN,
   TS_POLLPRI  = POLLPRI, 
   TS_POLLOUT  = POLLOUT,
   TS_POLLERR  = POLLERR,
   TS_POLLHUP  = POLLHUP,
   TS_POLLNVAL = POLLNVAL,
#endif
};

// ==== TYPES ====
// socket_t
typedef
#ifdef TINYSOCKET_WINSOCK
   SOCKET
#elseif TINYSOCKET_BSDSOCK
   int
#endif
   TINYSOCKET_ITEM(socket_t);
// pollfd_t
typedef
#ifdef TINYSOCKET_WINSOCK
   TINYSOCKET_NATIVE_ACCESS WSAPOLLFD
#elseif TINYSOCKET_BSDSOCK
   struct TINYSOCKET_NATIVE_ACCESS pollfd
#endif
   TINYSOCKET_ITEM(pollfd_t);
// nfds_t
typedef
#ifdef TINYSOCKET_WINSOCK
   TINYSOCKET_NATIVE_ACCESS ULONG
#elseif TINYSOCKET_BSDSOCK
   TINYSOCKET_NATIVE_ACCESS nfds_t
#endif
   TINYSOCKET_ITEM(pollfd_t);

// ==== FUNCTIONS ====
//socket
TINYSOCKET_FUNCTION(TINYSOCKET_ITEM(socket_t), socket)(int domain, int type, int protocol)
{
   return TINYSOCKET_NATIVE_ACCESS socket(domain, type, protocol);
}
//poll
TINYSOCKET_FUNCTION(int(pollfd_t *fds, TINYSOCKET_ITEM(nfds_t) nfds, int timeout)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS WSAPoll(fds, nfds, timeout);
#elseif TINYSOCKET_BSDSOCK
   return TINYSOCKET_NATIVE_ACCESS poll(fds, nfds, timeout);
#endif
}

#undef TINYSOCKET_PREFIX
#undef TINYSOCKET_CONCAT
#undef TINYSOCKET_CONCAT2
#undef TINYSOCKET_ITEM
#undef TINYSOCKET_FUNCTION
#undef TINYSOCKET_NATIVE_CALL

#endif //TINYSOCKET_H