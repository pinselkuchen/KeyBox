#ifndef SITASYCRYPT_H
#define SITASYCRYPT_H

#include <rsa.h>

namespace sit

{
class AsyCrypt
{
public:
    AsyCrypt();
    ~AsyCrypt();
    void createKeyPair(std::string *pub_key, std::string *priv_key);
private:
    void EncodeKeyBase64(CryptoPP::BufferedTransformation &bt, std::string *key);
    void EncodePublicKeyToString(CryptoPP::RSA::PublicKey &key, std::string *pub_key);
    void EncodePrivateKeyToString(CryptoPP::RSA::PrivateKey &key, std::string *priv_key);
    void DecodeKeyBase64(std::string &key, CryptoPP::BufferedTransformation *bt);
    void DecodePublicKeyFromString(std::string &pub_key, CryptoPP::RSA::PublicKey *key);
    void DecodePrivateKeyFromString(std::string &priv_key, CryptoPP::RSA::PrivateKey *key);
};
}

#endif // SITASYCRYPT_H
