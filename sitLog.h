#ifndef SITLOG_H
#define SITLOG_H

#include <iostream>

#define SIT_INFO  std::cout << "[INFO] | "
#define SIT_DEV(info)   std::cout<< "[DEV] " << info << "| "
#define SIT_WARN(info)  std::cout<< "[WARNING] " << info << "| "
#define SIT_ERROR(info) std::cout<< "[ERROR] " << info << "| "
#define SIT_DEBUG(info) std::cout<< "[DEBUG] " << info << "| "


#endif // SITLOG_H
