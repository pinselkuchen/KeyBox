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
    void CreateKeyPair(std::string *pub_key, std::string *priv_key);
    bool EncryptData(std::string pub_key, std::string data, std::string *enc_data);
    bool DecryptData(std::string priv_key, std::string *data, std::string enc_data);
private:
    void EncodeKey(CryptoPP::BufferedTransformation &bt, std::string *key);
    void EncodeKeyBase64(CryptoPP::BufferedTransformation &bt, std::string *key);
    void EncodePublicKeyToString(CryptoPP::RSA::PublicKey &key, std::string *pub_key);
    void EncodePrivateKeyToString(CryptoPP::RSA::PrivateKey &key, std::string *priv_key);
    void DecodeKey(std::string &key, CryptoPP::BufferedTransformation *bt);
    void DecodeKeyBase64(std::string &key, CryptoPP::BufferedTransformation *bt);
    void DecodePublicKeyFromString(std::string &pub_key, CryptoPP::RSA::PublicKey *key);
    void DecodePrivateKeyFromString(std::string &priv_key, CryptoPP::RSA::PrivateKey *key);
};
}

#endif // SITASYCRYPT_H
