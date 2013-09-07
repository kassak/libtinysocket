#ifndef TINYSOCKETMANIP_H
#define TINYSOCKETMANIP_H

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
TINYSOCKET_FUNCTION(int, getsockopt)(TINYSOCKET_ITEM(socket_t) sock, int level, int optname, void * optval, unsigned int * optlen)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS getsockopt(sock, level, optname, (char*)optval, optlen);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS getsockopt(sock, level, optname, optval, optlen);
#endif
}
//setsockopt
TINYSOCKET_FUNCTION(int, setsockopt)(TINYSOCKET_ITEM(socket_t) sock, int level, int optname, const void *optval, unsigned int optlen)
{
#ifdef TINYSOCKET_WINSOCK
   return TINYSOCKET_NATIVE_ACCESS setsockopt(sock, level, optname, (const char*)optval, optlen);
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS setsockopt(sock, level, optname, optval, optlen);
#endif
}
//connect
TINYSOCKET_FUNCTION(int, connect)(TINYSOCKET_ITEM(socket_t) sock, const TINYSOCKET_ITEM(sockaddr_t)* addr, unsigned int addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS connect(sock, addr, addrlen);
}
//getpeername
TINYSOCKET_FUNCTION(int, getpeername)(TINYSOCKET_ITEM(socket_t) sock, TINYSOCKET_ITEM(sockaddr_t) * addr, unsigned int * addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS getpeername(sock, addr, addrlen);
}
//getsockname
TINYSOCKET_FUNCTION(int, getsockname)(TINYSOCKET_ITEM(socket_t) sock, TINYSOCKET_ITEM(sockaddr_t) * addr, unsigned int * addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS getsockname(sock, addr, addrlen);
}
//bind
TINYSOCKET_FUNCTION(int, bind)(TINYSOCKET_ITEM(socket_t) sock, const TINYSOCKET_ITEM(sockaddr_t) *addr, unsigned int addrlen)
{
   return TINYSOCKET_NATIVE_ACCESS bind(sock, addr, addrlen);
}
//listen
TINYSOCKET_FUNCTION(int, listen)(TINYSOCKET_ITEM(socket_t) sock, int backlog)
{
   return TINYSOCKET_NATIVE_ACCESS listen(sock, backlog);
}
//accept
TINYSOCKET_FUNCTION(int, accept)(TINYSOCKET_ITEM(socket_t) sock, TINYSOCKET_ITEM(sockaddr_t) *addr, unsigned int *addrlen)
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
//fcntl
TINYSOCKET_FUNCTION(int, fcntl)(TINYSOCKET_ITEM(socket_t) sock, int cmd, int arg)
{
   return TINYSOCKET_NATIVE_ACCESS fcntl(sock, cmd, arg);
}


#endif //TINYSOCKETMANIP_H
