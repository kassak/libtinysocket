#ifndef TINYADDRESS_H
#define TINYADDRESS_H

//recv
TINYSOCKET_FUNCTION(int, inet_pton)(int af, const char *src, void *dst)
{
#ifdef TINYSOCKET_WINSOCK
   TINSOCKET_NO_REALISATION
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS inet_pton(af, src, dst);
#endif
}

TINYSOCKET_FUNCTION(const char*, inet_ntop)(int af, const void *src, char *dst, socklen_t size)
{
#ifdef TINYSOCKET_WINSOCK
   TINSOCKET_NO_REALISATION
#elif defined(TINYSOCKET_BSDSOCK)
   return TINYSOCKET_NATIVE_ACCESS inet_ntop(af, src, dst, size);
#endif
}
#endif //TINYADDRESS_H
