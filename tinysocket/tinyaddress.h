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

#endif //TINYADDRESS_H
