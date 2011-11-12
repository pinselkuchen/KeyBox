#ifndef SITHASHSEC_H
#define SITHASHSEC_H

#include <string>

namespace sit

{
class HashSec
{
public:
    HashSec();
    ~HashSec();
    void CalculateDigits(std::string pwd, std::string *hash);
};
}

#endif // SITHASHSEC_H
