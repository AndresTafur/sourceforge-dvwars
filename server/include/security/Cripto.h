#ifndef _WARSERVER_CRIPTO_H_
#define _WARSERVER_CRIPTO_H_

#include <string>
#include <gcrypt.h>

class Cripto
{
  protected:

        /** Default constructor */
        Cripto();

 public:

        static Cripto& getInstance();

        static Cripto* getInstancePtr();

        static void initialize();


        void setKey(const char key[17]);

        void setIv(const char iv[17]);

        std::string crypt(std::string data);

        std::string decrypt(std::string data);

        static void destroy();

        virtual ~Cripto();

protected:

        std::string fill(std::string data);

        void printError(std::string data);

private:
static Cripto *sm_instance;

gcry_cipher_hd_t m_handler;
size_t m_index;
size_t m_keyLength;
size_t m_blkLength;
char   m_symKey[16];
char   m_iv[16];
};

#endif // _WARSERVER_CRIPTO_H_
