#ifndef _WARSERVER_USERMANAGER_H_
#define _WARSERVER_USERMANAGER_H_

#include <string>

#include "persistance/MySQL.h"
#include "util/ConfigReader.h"

class UserDAO
{
    public:
        /** Default constructor */
        UserDAO();


        bool addUser(std::string user, std::string password, std::string email, std::string idCity);


        bool validate(std::string user, std::string password);


        bool logOut(std::string user);


        /** Default destructor */
        virtual ~UserDAO();

private:
MySQL *m_sqlHandler;



};

#endif // _WARSERVER_USERMANAGER_H_
