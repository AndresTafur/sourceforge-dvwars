#include "Cripto.h"
#include <iostream>
#include <stdio.h>

Cripto * Cripto::sm_instance = 0;

Cripto::Cripto()
{
gcry_error_t     gcryError;
std::string str;

    m_keyLength = gcry_cipher_get_algo_keylen(GCRY_CIPHER_AES128);
    m_blkLength = gcry_cipher_get_algo_blklen(GCRY_CIPHER_AES128);

    gcryError = gcry_cipher_open(&m_handler,GCRY_CIPHER_AES128,GCRY_CIPHER_MODE_ECB,0);

    if (gcryError)
    {
        str = "gcry_cipher_open failed: ";
        str += gcry_strsource(gcryError);
        str += " , ";
        str += gcry_strerror(gcryError);
        str += ".";
        throw str;
    }
}


    Cripto& Cripto::getInstance()
    {
        if(!sm_instance)
            sm_instance = new Cripto();

        return *sm_instance;
    }

    Cripto* Cripto::getInstancePtr()
    {
        if(!sm_instance)
            sm_instance = new Cripto();

        return sm_instance;
    }

    void Cripto::initialize()
    {
       gcry_control (GCRYCTL_DISABLE_SECMEM, 0);
       gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);
    }

    void Cripto::setKey(const char key[17])
    {
      gcry_error_t gcryError;

            strcpy(m_symKey,key);
            gcryError = gcry_cipher_setkey(m_handler, m_symKey, m_keyLength);
            if (gcryError)
              printf("gcry_cipher_setkey failed:  %s/%s\n", gcry_strsource(gcryError), gcry_strerror(gcryError));
     }

    void Cripto::setIv(const char iv[17])
    {
      gcry_error_t gcryError;

            strcpy(m_iv,iv);
            gcryError = gcry_cipher_setiv(m_handler, m_iv, m_blkLength);
            if (gcryError)

             printf("gcry_cipher_setIv failed:  %s/%s\n", gcry_strsource(gcryError), gcry_strerror(gcryError));
    }



    std::string Cripto::crypt(std::string str)
    {
      gcry_error_t     gcryError;
      char* encBuffer = new char[130];
      char buff[1];

        str = fill(str);

        setIv(m_iv);
        gcryError = gcry_cipher_encrypt(m_handler,  encBuffer,  130,  str.c_str(), str.size()+1);   // size_t
        if (gcryError)
        {
            str += "\n";
            str += "gcry_cipher_encrypt failed: ";
            str += gcry_strsource(gcryError);
            str += " , ";
            str += gcry_strerror(gcryError);
            str += ".";
            throw str;
        }

        str = "";

        for (int index = 0; index<64; index++)
        {
           sprintf(buff,"%02X", (unsigned char)encBuffer[index]);
           str += buff;
        }

        return str;
    }

    std::string Cripto::decrypt(std::string data)
    {
      gcry_error_t     gcryError;
      unsigned char encBuffer[64];
      char decBuffer[64];
      char buff[3];
      unsigned int val;
      std::string str;

        setIv(m_iv);

        for(unsigned int i=0,j=0; j < 64;i++,j++)
        {
            buff[0] = data.at(i);
            buff[1] = data.at(++i);
            buff[2] = '\0';
            sscanf(buff,"%X",&val);
            encBuffer[j] = val;
        }

        gcryError = gcry_cipher_decrypt(m_handler,  decBuffer,  64,  encBuffer, 64);   // size_t
        if (gcryError)
        {
            str  = "gcry_cipher_decrypt failed: ";
            str += gcry_strsource(gcryError);
            str += " , ";
            str += gcry_strerror(gcryError);
            str += ".";
            std::cerr << str;
        }

        return std::string(decBuffer);
    }

    void Cripto::destroy()
    {

        delete sm_instance;
    }

    std::string Cripto::fill(std::string str)
    {
       char  data[64];

        strcpy(data,str.c_str());

        while( strlen(data) < 63)
            strcat(data,"Z");

        return data;
    }


Cripto::~Cripto()
{
    gcry_cipher_close (m_handler);
}
