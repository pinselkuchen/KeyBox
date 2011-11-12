#include "sitAsyCrypt.h"

#include <osrng.h>
#include <queue.h>
#include <base64.h>
#include <files.h>

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



void sit::AsyCrypt::test()
{
    sit::AsyCrypt *hans = new sit::AsyCrypt();

    std::string publicKey;
    std::string privateKey;

    hans->CreateKeyPair(&publicKey, &privateKey);

    std::cout << std::endl;
    std::cout << "PubKey: " << publicKey << std::endl;
    std::cout << "PrivKey: " << privateKey << std::endl;

    std::string text = "Dies ist ein unverschluesselter Text!";
    std::string cipher, plain;

    hans->EncryptData(publicKey, text, &cipher);

    std::cout << "text: " << text << std::endl;
    std::cout << "cipher: " << cipher << std::endl;

    hans->DecryptData(privateKey, &plain, cipher);

    std::cout << "text: " << text << std::endl;
    std::cout << "plain: " << plain << std::endl;
}




void sit::AsyCrypt::CreateKeyPair(std::string *pub_key, std::string *priv_key)
{
    CryptoPP::AutoSeededRandomPool rng;

    std::string tmpPubKey;
    std::string tmpPrivKey;

    CryptoPP::RSA::PrivateKey privateKey;
    privateKey.GenerateRandomWithKeySize(rng, 1024);
    CryptoPP::RSA::PublicKey publicKey(privateKey);

    tmpPubKey = EncodePublicKeyToString(publicKey);
    tmpPrivKey = EncodePrivateKeyToString(privateKey);

    *pub_key = EncodeStringBase64(tmpPubKey);
    *priv_key = EncodeStringBase64(tmpPrivKey);
}



/******************** EN- & DECRYPTION ********************/

bool sit::AsyCrypt::EncryptData(std::string pub_key, std::string data, std::string *enc_data)
{
    CryptoPP::AutoSeededRandomPool rng;

    std::string tmpData;
    std::string tmpPubKey = DecodeStringBase64(pub_key);

    CryptoPP::RSA::PublicKey publicKey;
    DecodePublicKeyFromString(tmpPubKey, &publicKey);

    try
    {
        CryptoPP::RSAES_OAEP_SHA_Encryptor encryptor( publicKey );
        CryptoPP::StringSource( data, true, new CryptoPP::PK_EncryptorFilter( rng, encryptor, new CryptoPP::StringSink( tmpData ) ) );
        *enc_data = EncodeStringBase64(tmpData);
    }
    catch ( CryptoPP::Exception &e )
    {
        cerr << "sit::AsyCrypt::EncryptData Caught Exception..." << endl;
        cerr << e.what() << endl;

        return false;
    }

    return true;
}

bool sit::AsyCrypt::DecryptData(std::string priv_key, std::string *data, std::string enc_data)
{
    CryptoPP::AutoSeededRandomPool rng;

    std::string tmpData = DecodeStringBase64(enc_data);
    std::string tmpPrivKey = DecodeStringBase64(priv_key);

    CryptoPP::RSA::PrivateKey privateKey;
    DecodePrivateKeyFromString(tmpPrivKey, &privateKey);

    try
    {
        CryptoPP::RSAES_OAEP_SHA_Decryptor decryptor( privateKey );
        CryptoPP::StringSource( tmpData, true, new CryptoPP::PK_DecryptorFilter( rng, decryptor, new CryptoPP::StringSink( *data ) ) );
    }
    catch ( CryptoPP::Exception &e )
    {
        cerr << "sit::AsyCrypt::DecryptData Caught Exception..." << endl;
        cerr << e.what() << endl;

        return false;
    }

    return true;
}



/******************** KEY EN- & DECODING ********************/

void sit::AsyCrypt::EncodeKey(CryptoPP::BufferedTransformation &bt, std::string *key)
{
    CryptoPP::StringSink name(*key);
    bt.CopyTo(name);
    name.MessageEnd();
}

std::string sit::AsyCrypt::EncodePublicKeyToString(CryptoPP::RSA::PublicKey &key)
{
    std::string pub_key;

    CryptoPP::ByteQueue queue;
    key.DEREncodePublicKey(queue);
    EncodeKey(queue, &pub_key);

    return pub_key;
}

std::string sit::AsyCrypt::EncodePrivateKeyToString(CryptoPP::RSA::PrivateKey &key)
{
    std::string priv_key;

    CryptoPP::ByteQueue queue;
    key.DEREncodePrivateKey(queue);
    EncodeKey(queue, &priv_key);

    return priv_key;
}

void sit::AsyCrypt::DecodeKey(std::string &key, CryptoPP::BufferedTransformation *bt)
{
    CryptoPP::StringSource file(key, true);
    file.TransferTo(*bt);
    bt->MessageEnd();
}

void sit::AsyCrypt::DecodePublicKeyFromString(std::string &pub_key, CryptoPP::RSA::PublicKey *key)
{
    CryptoPP::ByteQueue queue;
    DecodeKey(pub_key, &queue);
    key->BERDecodePublicKey(queue, false, queue.MaxRetrievable());
}

void sit::AsyCrypt::DecodePrivateKeyFromString(std::string &priv_key, CryptoPP::RSA::PrivateKey *key)
{
    CryptoPP::ByteQueue queue;
    DecodeKey(priv_key, &queue);
    key->BERDecodePrivateKey(queue, false, queue.MaxRetrievable());
}



/******************** BASE64 ********************/

std::string sit::AsyCrypt::EncodeStringBase64(std::string text)
{
    std::string tmp;
    CryptoPP::StringSource(text, true, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(tmp)));
    return tmp;
}

std::string sit::AsyCrypt::DecodeStringBase64(std::string text)
{
    std::string tmp;
    CryptoPP::StringSource(text, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(tmp)));
    return tmp;
}
