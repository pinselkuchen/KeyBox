#include "sitAsyCrypt.h"

#include <osrng.h>
#include <queue.h>
#include <base64.h>
#include <files.h>

#include <string.h>

#include <exception>
using std::exception;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

sit::AsyCrypt::AsyCrypt()
{
}

sit::AsyCrypt::~AsyCrypt()
{
}

bool sit::AsyCrypt::EncryptData(std::string pub_key, std::string data, std::string *enc_data)
{
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::RSA::PublicKey publicKey;
    DecodePublicKeyFromString(pub_key, &publicKey);

    try
    {
        CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor( publicKey );
        CryptoPP::StringSource( data, true, new CryptoPP::PK_EncryptorFilter( rng, encryptor, new CryptoPP::StringSink( *enc_data ) ) );
    }
    catch ( CryptoPP::Exception &e )
    {
        cerr << "sit::AsyCrypt::EncryptData Caught Exception..." << endl;
        cerr << e.what() << endl;
    }

    return true;
}

bool sit::AsyCrypt::DecryptData(std::string priv_key, std::string *data, std::string enc_data)
{
    CryptoPP::AutoSeededRandomPool rng;

    CryptoPP::RSA::PrivateKey privateKey;
    DecodePrivateKeyFromString(priv_key, &privateKey);

    try
    {
        CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor( privateKey );
        CryptoPP::StringSource( enc_data, true, new CryptoPP::PK_DecryptorFilter( rng, decryptor, new CryptoPP::StringSink( *data ) ) );
    }
    catch ( CryptoPP::Exception &e )
    {
        cerr << "sit::AsyCrypt::DecryptData Caught Exception..." << endl;
        cerr << e.what() << endl;
    }

    return true;
}

void sit::AsyCrypt::CreateKeyPair(std::string *pub_key, std::string *priv_key)
{
    try
    {
        CryptoPP::AutoSeededRandomPool rng;

        CryptoPP::RSA::PrivateKey privateKey;
        privateKey.GenerateRandomWithKeySize(rng, 1024);
        CryptoPP::RSA::PublicKey publicKey(privateKey);

        EncodePublicKeyToString(publicKey, pub_key);
        EncodePrivateKeyToString(privateKey, priv_key);
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::CreateKeyPair" << endl;
    }
}

void sit::AsyCrypt::EncodeKey(CryptoPP::BufferedTransformation &bt, std::string *key)
{
    try
    {
        CryptoPP::StringSink name(*key);
        bt.CopyTo(name);
        name.MessageEnd();
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::EncodeKeyBase64" << endl;
    }
}

void sit::AsyCrypt::EncodeKeyBase64(CryptoPP::BufferedTransformation &bt, std::string *key)
{
    try
    {
        CryptoPP::StringSink name(*key);
        CryptoPP::Base64Encoder encoder;
        bt.CopyTo(encoder);
        encoder.MessageEnd();
        encoder.CopyTo(name);
        name.MessageEnd();
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::EncodeKeyBase64" << endl;
    }
}

void sit::AsyCrypt::EncodePublicKeyToString(CryptoPP::RSA::PublicKey &key, std::string *pub_key)
{
    try
    {
        CryptoPP::ByteQueue queue;
        key.DEREncodePublicKey(queue);
        //EncodeKeyBase64(queue, pub_key);
        EncodeKey(queue, pub_key);
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::EncodePublicKeyToString" << endl;
    }
}

void sit::AsyCrypt::EncodePrivateKeyToString(CryptoPP::RSA::PrivateKey &key, std::string *priv_key)
{
    try
    {
        CryptoPP::ByteQueue queue;
        key.DEREncodePrivateKey(queue);
        //EncodeKeyBase64(queue, priv_key);
        EncodeKey(queue, priv_key);
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::EncodePrivateKeyToString" << endl;
    }
}

void sit::AsyCrypt::DecodeKey(std::string &key, CryptoPP::BufferedTransformation *bt)
{
    try
    {
        CryptoPP::StringSource file(key, true /*pumpAll*/);
        file.TransferTo(*bt);
        bt->MessageEnd();
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::DecodeKeyBase64" << endl;
    }
}

void sit::AsyCrypt::DecodeKeyBase64(std::string &key, CryptoPP::BufferedTransformation *bt)
{
    try
    {
        CryptoPP::StringSource file(key, true /*pumpAll*/);
        CryptoPP::Base64Decoder decoder;
        file.TransferTo(decoder);
        decoder.TransferTo(*bt);
        bt->MessageEnd();
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::DecodeKeyBase64" << endl;
    }
}

void sit::AsyCrypt::DecodePublicKeyFromString(std::string &pub_key, CryptoPP::RSA::PublicKey *key)
{
    try
    {
        CryptoPP::ByteQueue queue;
        DecodeKey(pub_key, &queue);
        //DecodeKeyBase64(pub_key, &queue);
        key->BERDecodePublicKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::DecodePublicKeyFromString" << endl;
    }
}

void sit::AsyCrypt::DecodePrivateKeyFromString(std::string &priv_key, CryptoPP::RSA::PrivateKey *key)
{
    try
    {
        CryptoPP::ByteQueue queue;
        DecodeKey(priv_key, &queue);
        //DecodeKeyBase64(priv_key, &queue);
        key->BERDecodePrivateKey(queue, false /*paramsPresent*/, queue.MaxRetrievable());
    }
    catch (...)
    {
        cerr << "sit::AsyCrypt::DecodePrivateKeyFromString" << endl;
    }
}
