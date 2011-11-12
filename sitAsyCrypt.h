#ifndef SITASYCRYPT_H
#define SITASYCRYPT_H

#include <rsa.h>

#include <string>

namespace sit

{
class AsyCrypt
{
public:
    AsyCrypt();
    ~AsyCrypt();
    void test();
    void CreateKeyPair(std::string *pub_key, std::string *priv_key);
    bool EncryptData(std::string pub_key, std::string data, std::string *enc_data);
    bool DecryptData(std::string priv_key, std::string *data, std::string enc_data);
private:
    void EncodeKey(CryptoPP::BufferedTransformation &bt, std::string *key);
    std::string EncodePublicKeyToString(CryptoPP::RSA::PublicKey &key);
    std::string EncodePrivateKeyToString(CryptoPP::RSA::PrivateKey &key);
    void DecodeKey(std::string &key, CryptoPP::BufferedTransformation *bt);
    void DecodePublicKeyFromString(std::string &pub_key, CryptoPP::RSA::PublicKey *key);
    void DecodePrivateKeyFromString(std::string &priv_key, CryptoPP::RSA::PrivateKey *key);
    std::string EncodeStringBase64(std::string text);
    std::string DecodeStringBase64(std::string text);
};
}

#endif // SITASYCRYPT_H
