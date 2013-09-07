#ifndef TINYBITS_H
#define TINYBITS_H

#ifdef TINYSOCKET_WINSOCK
   static const TINYSOCKET_ITEM(socket_t) TS_SOCKET_ERROR = (TINYSOCKET_ITEM(socket_t))SOCKET_ERROR;
#elif defined(TINYSOCKET_BSDSOCK)
   static const TINYSOCKET_ITEM(socket_t) TS_SOCKET_ERROR = (TINYSOCKET_ITEM(socket_t))-1;
#endif
enum
{
   TS_NO_ERROR = 0,
};

enum TINYSOCKET_ITEM(fcntl_cmds_t)
{
   TS_F_SETFL = F_SETFL,
};

enum TINYSOCKET_ITEM(sflags_t)
{
   TS_O_NONBLOCK = O_NONBLOCK,
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
   TINYSOCKET_EITEM(EAGAIN)
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
};

#undef TINYSOCKET_EITEM


#endif //TINYBITS_H
