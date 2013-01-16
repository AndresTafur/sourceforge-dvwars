#ifndef DBEXCEPTION_H_
#define DBEXCEPTION_H_

#include <exception>


class DBException : public std::exception
{
public:

        DBException(std::string msg) { mType = msg;}


        virtual const char* what() const throw(){ return mType.c_str(); }

        ~DBException() throw() { }

private:
std::string mType;
};

#endif // DBEXCEPTION_H_
