#ifndef TINYTYPES_H
#define TINYTYPES_H

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
   TINYSOCKET_ITEM(hostent_t);
// pollfd_t
typedef
#ifdef TINYSOCKET_WINSOCK
   TINYSOCKET_NATIVE_ACCESS WSAPOLLFD
#elif defined(TINYSOCKET_BSDSOCK)
   struct TINYSOCKET_NATIVE_ACCESS pollfd
#endif
   TINYSOCKET_ITEM(pollfd_t);


#endif //TINYTYPES_H
