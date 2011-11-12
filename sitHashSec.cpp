#include "sitHashSec.h"

#include <sha.h>
#include <base64.h>

sit::HashSec::HashSec()
{
}

sit::HashSec::~HashSec()
{
}

void sit::HashSec::CalculateDigits(std::string pwd, std::string *hash)
{
    CryptoPP::SHA256 tmpHash;
    CryptoPP::StringSource foo(pwd, true, new CryptoPP::HashFilter(tmpHash, new CryptoPP::Base64Encoder ( new CryptoPP::StringSink( *hash ) )));
}
