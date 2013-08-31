#ifndef TINYUTILS_H
#define TINYUTILS_H

//htonl
TINYSOCKET_FUNCTION(uint32_t, htonl)(uint32_t hostlong)
{
   return TINYSOCKET_NATIVE_ACCESS htonl(hostlong);
}

//htons
TINYSOCKET_FUNCTION(uint16_t, htons)(uint16_t hostshort)
{
   return TINYSOCKET_NATIVE_ACCESS htons(hostshort);
}

//ntohl
TINYSOCKET_FUNCTION(uint32_t, ntohl)(uint32_t netlong)
{
   return TINYSOCKET_NATIVE_ACCESS ntohl(netlong);
}

//ntohs
TINYSOCKET_FUNCTION(uint16_t, ntohs)(uint16_t netshort)
{
   return TINYSOCKET_NATIVE_ACCESS ntohs(netshort);
}

#endif //TINYUTILS_H
