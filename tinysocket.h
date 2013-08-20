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
#define TINYSOCKET_FUNCTION(RET, FOO) inline RET TINYSOCKET_ITEM(FOO)
// In C there must be prefix in C++ there must be namespace
// that is why native is called from global scope
#ifndef __cplusplus
   #define TINYSOCKET_NATIVE_ACCESS
#else
   #define TINYSOCKET_NATIVE_ACCESS ::
#endif

// ==== CONSTANTS ====
enum
{
#ifdef TINYSOCKET_WINSOCK
  TS_SOCKET_ERROR = SOCKET_ERROR,
#elif defined(TINYSOCKET_BSDSOCK)
  TS_SOCKET_ERROR = -1,
#endif
  TS_NO_ERROR = 0,
};

enum TINYSOCKET_ITEM(poll_events_t)
{
#ifdef TINYSOCKET_WINSOCK
   TS_POLLIN   = POLLRDNORM,
   TS_POLLPRI  = POLLPRI,
   TS_POLLOUT  = POLLWRNORM,
   TS_POLLERR  = POLLERR,
   TS_POLLHUP  = POLLHUP,
   TS_POLLNVAL = POLLNVAL,
#elif defined(TINYSOCKET_BSDSOCK)
   TS_POLLIN   = POLLIN,
   TS_POLLPRI  = POLLPRI,
   TS_POLLOUT  = POLLOUT,
   TS_POLLERR  = POLLERR,
   TS_POLLHUP  = POLLHUP,
   TS_POLLNVAL = POLLNVAL,
#endif
};

#ifdef TINYSOCKET_WINSOCK
   #define TINYSOCKET_EITEM(X) TS_##X = WSA##X,
#elif defined(TINYSOCKET_BSDSOCK)
   #define TINYSOCKET_EITEM(X) TS_##X = X,
#endif

enum TINYSOCKET_ITEM(errno_t)
{
   TINYSOCKET_EITEM(EWOULDBLOCK)
   TINYSOCKET_EITEM(EINPROGRESS)
   TINYSOCKET_EITEM(EALREADY)
   TINYSOCKET_EITEM(ENOTSOCK)
   TINYSOCKET_EITEM(EDESTADDRREQ)
   TINYSOCKET_EITEM(EMSGSIZE)
   TINYSOCKET_EITEM(EPROTOTYPE)
   TINYSOCKET_EITEM(ENOPROTOOPT)
   TINYSOCKET_EITEM(EPROTONOSUPPORT)
   TINYSOCKET_EITEM(ESOCKTNOSUPPORT)
   TINYSOCKET_EITEM(EOPNOTSUPP)
   TINYSOCKET_EITEM(EPFNOSUPPORT)
   TINYSOCKET_EITEM(EAFNOSUPPORT)
   TINYSOCKET_EITEM(EADDRINUSE)
   TINYSOCKET_EITEM(EADDRNOTAVAIL)
   TINYSOCKET_EITEM(ENETDOWN)
   TINYSOCKET_EITEM(ENETUNREACH)
   TINYSOCKET_EITEM(ENETRESET)
   TINYSOCKET_EITEM(ECONNABORTED)
   TINYSOCKET_EITEM(ECONNRESET)
   TINYSOCKET_EITEM(ENOBUFS)
   TINYSOCKET_EITEM(EISCONN)
   TINYSOCKET_EITEM(ENOTCONN)
   TINYSOCKET_EITEM(ESHUTDOWN)
   TINYSOCKET_EITEM(ETOOMANYREFS)
   TINYSOCKET_EITEM(ETIMEDOUT)
   TINYSOCKET_EITEM(ECONNREFUSED)
   TINYSOCKET_EITEM(ELOOP)
   TINYSOCKET_EITEM(ENAMETOOLONG)
   TINYSOCKET_EITEM(EHOSTDOWN)
   TINYSOCKET_EITEM(EHOSTUNREACH)
   TINYSOCKET_EITEM(ENOTEMPTY)
      //   TINYSOCKET_EITEM(EPROCLIM)
   TINYSOCKET_EITEM(EUSERS)
   TINYSOCKET_EITEM(EDQUOT)
   TINYSOCKET_EITEM(ESTALE)
   TINYSOCKET_EITEM(EREMOTE)
};

enum TINYSOCKET_ITEM(flags_t)
{
   TS_MSG_PEEK      = MSG_PEEK,
   TS_MSG_OOB       = MSG_OOB,
   TS_MSG_WAITALL   = MSG_WAITALL,
   TS_MSG_DONTROUTE = MSG_DONTROUTE,
};

enum TINYSOCKET_ITEM(address_family_t)
{
   TS_AF_INET   = AF_INET,
   TS_AF_INET6  = AF_INET6,
   TS_AF_IPX    = AF_IPX,
};

enum TINYSOCKET_ITEM(socket_type_t)
{
   TS_SOCK_STREAM    = SOCK_STREAM,
   TS_SOCK_DGRAM     = SOCK_DGRAM,
   TS_SOCK_RAW       = SOCK_RAW,
   TS_SOCK_RDM       = SOCK_RDM,
   TS_SOCK_SEQPACKET = SOCK_SEQPACKET,
};

enum TINYSOCKET_ITEM(proto_type_t)
{
   TS_IPPROTO_UNSPECIFIED = 0,
   TS_IPPROTO_ICMP = IPPROTO_ICMP,
   TS_IPPROTO_IGMP = IPPROTO_IGMP,
   TS_IPPROTO_TCP  = IPPROTO_TCP,
   TS_IPPROTO_UDP  = IPPROTO_UDP,
};

enum TINYSOCKET_ITEM(shutdown_type_t)
{
#ifdef TINYSOCKET_WINSOCK
  TS_SHUT_RD   = SD_RECEIVE,
  TS_SHUT_WR   = SD_SEND,
  TS_SHUT_RDWR = SD_BOTH,
#elif defined(TINYSOCKET_BSDSOCK)
  TS_SHUT_RD   = SHUT_RD,
  TS_SHUT_WR   = SHUT_WR,
  TS_SHUT_RDWR = SHUT_RDWR,
#endif
}

#undef TINYSOCKET_EITEM


// ==== TYPES ====
// socket_t
typedef
#ifdef TINYSOCKET_WINSOCK
   SOCKET
#elseif TINYSOCKET_BSDSOCK
   int
#endif
   TINYSOCKET_ITEM(socket_t);
// sockaddr
typedef
   struct TINYSOCKET_NATIVE_ACCESS sockaddr
   TINYSOCKET_ITEM(sockaddr_t);
// sockaddr_in
typedef
   struct TINYSOCKET_NATIVE_ACCESS sockaddr_in
   TINYSOCKET_ITEM(sockaddr_in_t);
// sockaddr_in6
typedef
   struct TINYSOCKET_NATIVE_ACCESS sockaddr_in6
   TINYSOCKET_ITEM(sockaddr_in6_t);
// in_addr
typedef
   struct TINYSOCKET_NATIVE_ACCESS in_addr
   TINYSOCKET_ITEM(in_addr_t);
// in6_addr
typedef
   struct TINYSOCKET_NATIVE_ACCESS in6_addr
   TINYSOCKET_ITEM(in6_addr_t);
// sockaddr_storage
typedef
   struct TINYSOCKET_NATIVE_ACCESS sockaddr_storage
   TINYSOCKET_ITEM(sockaddr_storage_t);
//  hostent
typedef
    struct hostent
    hostent_t;
// pollfd_t
typedef
#ifdef TINYSOCKET_WINSOCK
   TINYSOCKET_NATIVE_ACCESS WSAPOLLFD
#elif defined(TINYSOCKET_BSDSOCK)
   struct TINYSOCKET_NATIVE_ACCESS pollfd
#endif
   TINYSOCKET_ITEM(pollfd_t);

// ==== FUNCTIONS ====
//errno
TINYSOCKET_FUNCTION(int, last_error)()
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS WSAGetLastError();
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS errno;
#endif
}
//init
TINYSOCKET_FUNCTION(int, init)()
{
#ifdef TINYSOCKET_WINSOCK
   //let's fuck M$ together
   WORD wVersionRequested = MAKEWORD(2, 2);
   WSADATA wsaData;
   return TINYSOCKET_NATIVE_ACCESS WSAStartup(wVersionRequested, &wsaData);
#elif defined(TINYSOCKET_BSDSOCK)
   return 0;
#endif
}
//deinit
TINYSOCKET_FUNCTION(int, deinit)()
{
#ifdef TINYSOCKET_WINSOCK
   //let's fuck M$ together
   return TINYSOCKET_NATIVE_ACCESS WSACleanup();
#elif defined(TINYSOCKET_BSDSOCK)
   return 0;
#endif
}
//socket
TINYSOCKET_FUNCTION(TINYSOCKET_ITEM(socket_t), socket)(int domain, int type, int protocol)
{
   return TINYSOCKET_NATIVE_ACCESS socket(domain, type, protocol);
}
//close
TINYSOCKET_FUNCTION(int, close)(TINYSOCKET_ITEM(socket_t) sock)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS closesocket(sock);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS close(sock);
#endif
}
//shutdown
TINYSOCKET_FUNCTION(int, shutdown)(TINYSOCKET_ITEM(socket_t) sock, int how)
{
   return TINYSOCKET_NATIVE_ACCESS shutdown(sock, how);
}
//getsockopt
TINYSOCKET_FUNCTION(int, getsockopt)(TINYSOCKET_ITEM(socket_t) sock, int level, int optname, void * optval, int * optlen)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS getsockopt(sock, level, optname, (char*)optval, optlen);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS getsockopt(sock, level, optname, optval, optlen);
#endif
}
//setsockopt
TINYSOCKET_FUNCTION(int, setsockopt)(TINYSOCKET_ITEM(socket_t) sock, int level, int optname, const void *optval, int optlen)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS setsockopt(sock, level, optname, (const char*)optval, optlen);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS setsockopt(sock, level, optname, optval, optlen);
#endif
}
//connect
TINYSOCKET_FUNCTION(int, connect)(TINYSOCKET_ITEM(socket_t) sock, const TINYSOCKET_ITEM(sockaddr_t)* addr, int addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS connect(sock, addr, addrlen);
}
//getpeername
TINYSOCKET_FUNCTION(int, getpeername)(TINYSOCKET_ITEM(socket_t) sock, TINYSOCKET_ITEM(sockaddr_t) * addr, int * addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS getpeername(sock, addr, addrlen);
}
//getsockname
TINYSOCKET_FUNCTION(int, getsockname)(TINYSOCKET_ITEM(socket_t) sock, TINYSOCKET_ITEM(sockaddr_t) * addr, int * addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS getsockname(sock, addr, addrlen);
}
//bind
TINYSOCKET_FUNCTION(int, bind)(TINYSOCKET_ITEM(socket_t) sock, const TINYSOCKET_ITEM(sockaddr_t) *addr, int addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS bind(sock, addr, addrlen);
}
//listen
TINYSOCKET_FUNCTION(int, listen)(TINYSOCKET_ITEM(socket_t) sock, int backlog)
{
   return TINYSOCKET_NATIVE_ACCESS listen(sock, backlog);
}
//accept
TINYSOCKET_FUNCTION(int, accept)(TINYSOCKET_ITEM(socket_t) sock, TINYSOCKET_ITEM(sockaddr_t) *addr, int *addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS accept(sock, addr, addrlen);
}
//poll
TINYSOCKET_FUNCTION(int, poll)(TINYSOCKET_ITEM(pollfd_t) *fds, int nfds, int timeout)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS WSAPoll(fds, nfds, timeout);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS poll(fds, nfds, timeout);
#endif
}
//recv
TINYSOCKET_FUNCTION(int, recv)(TINYSOCKET_ITEM(socket_t) sock, void * buf, size_t len, int flags)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS recv(sock, (char*)buf, len, flags);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS recv(sock, buf, len, flags);
#endif
}
//send
TINYSOCKET_FUNCTION(int, send)(TINYSOCKET_ITEM(socket_t) sock, const void * buf, size_t len, int flags)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS send(sock, (char*)buf, len, flags);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS send(sock, buf, len, flags);
#endif
}
//read
TINYSOCKET_FUNCTION(int, read)(TINYSOCKET_ITEM(socket_t) sock, void * buf, size_t len)
{
   return TINYSOCKET_ITEM(recv)(sock, buf, len, 0);
}
//write
TINYSOCKET_FUNCTION(int, write)(TINYSOCKET_ITEM(socket_t) sock, const void * buf, size_t len)
{
   return TINYSOCKET_ITEM(send)(sock, buf, len, 0);
}

#undef TINYSOCKET_PREFIX
#undef TINYSOCKET_CONCAT
#undef TINYSOCKET_CONCAT2
#undef TINYSOCKET_ITEM
#undef TINYSOCKET_FUNCTION
#undef TINYSOCKET_NATIVE_CALL

#endif //TINYSOCKET_H
