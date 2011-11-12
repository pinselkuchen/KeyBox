#include "sitAsyCrypt.h"

#include <osrng.h>
#include <queue.h>
#include <base64.h>
#include <files.h>

sit::AsyCrypt::AsyCrypt()
{
}

sit::AsyCrypt::~AsyCrypt()
{
}

void sit::AsyCrypt::createKeyPair(std::string *pub_key, std::string *priv_key)
{
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::RSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, 1024);
    CryptoPP::RSA::PublicKey publicKey(privateKey);

    EncodePublicKeyToString(publicKey, pub_key);
    EncodePrivateKeyToString(privateKey, priv_key);
}

void sit::AsyCrypt::EncodeKeyBase64(CryptoPP::BufferedTransformation &bt, std::string *key)
{
    CryptoPP::StringSink name(*key);
    CryptoPP::Base64Encoder encoder;
    bt.CopyTo(encoder);
    encoder.MessageEnd();
    encoder.CopyTo(name);
    name.MessageEnd();
}

void sit::AsyCrypt::EncodePublicKeyToString(CryptoPP::RSA::PublicKey &key, std::string *pub_key)
{
    CryptoPP::ByteQueue queue;
    key.DEREncodePublicKey(queue);
    EncodeKeyBase64(queue, pub_key);
}

void sit::AsyCrypt::EncodePrivateKeyToString(CryptoPP::RSA::PrivateKey &key, std::string *priv_key)
{
    CryptoPP::ByteQueue queue;
    key.DEREncodePrivateKey(queue);
    EncodeKeyBase64(queue, priv_key);
}

void sit::AsyCrypt::DecodeKeyBase64(std::string &key, CryptoPP::BufferedTransformation *bt)
{
   CryptoPP::StringSource file(key, true /*pumpAll*/);
   CryptoPP::Base64Decoder decoder;
   file.TransferTo(decoder);
   decoder.TransferTo(*bt);
   bt->MessageEnd();
}

void sit::AsyCrypt::DecodePublicKeyFromString(std::string &pub_key, CryptoPP::RSA::PublicKey *key)
{
    CryptoPP::ByteQueue queue;
    DecodeKeyBase64(pub_key, &queue);
    key->BERDecodePublicKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());
}

void sit::AsyCrypt::DecodePrivateKeyFromString(std::string &priv_key, CryptoPP::RSA::PrivateKey *key)
{
    CryptoPP::ByteQueue queue;
    DecodeKeyBase64(priv_key, &queue);
    key->BERDecodePrivateKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());
}
