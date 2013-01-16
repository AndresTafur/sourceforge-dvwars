#ifndef _NETWORKEXCEPTION_H_
#define _NETWORKEXCEPTION_H_

#include <exception>
#include <string>


class NetworkException : public std::exception
{
    public:
        /**
         *  Constructs the network exception based on msg.
         */
         NetworkException() { mType =  std::string(strerror(errno));  }

         NetworkException(std::string msg) { mType =  std::string(strerror(errno)) + msg;  }


        virtual const char* what() const throw(){ return mType.c_str(); }

        ~NetworkException() throw() { }

private:
std::string mType;
};

#endif // _NETWORKEXCEPTION_H_
