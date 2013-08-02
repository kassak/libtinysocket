#ifndef TINYSOCKET_HPP
#define TINYSOCKET_HPP

#ifndef TINYSOCKET_USER_NS
   #define TINYSOCKET_NS tinsock
#else
   #define TINYSOCKET_NS TINYSOCKET_USER_NS
#endif //TINYSOCKET_USER_NS

// Empty prefix, all inside namespace
#define TINYSOCKET_USER_PREFIX

namespace TINYSOCKET_NS
{

#include "tinysocket.h"

} //namespace TINYSOCKET_NS

#undef TINYSOCKET_USER_PREFIX

#endif //TINYSOCKET_HPP
