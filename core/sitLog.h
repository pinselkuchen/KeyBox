#ifndef SITLOG_H
#define SITLOG_H

#include <iostream>

// Logging trough mbilog
#if 1//def MES_USE_MBILOG
 #include "core/mbilog.h"
 #define SIT_INFO  MBI_INFO("sit")
 #define SIT_DEV   MBI_INFO("sit")
 #define SIT_WARN  MBI_WARN("sit")
 #define SIT_ERROR MBI_ERROR("sit")
 #define SIT_DEBUG MBI_ERROR("sit")
#else
 #include <iostream>
 #define SIT_INFO  std::cout
 #define SIT_DEV   std::cout
 #define SIT_WARN  std::cout
 #define SIT_ERROR std::cout
 #define SIT_DEBUG std::cout
#endif



namespace sit
{

}

#endif // SITLOG_H
