#ifndef _WS_LOGINMANAGER_H
#define _WS_LOGINMANAGER_H

#include <stdio.h>

#include "User.h"
#include "UserDAO.h"


/**
 * Manages user DAO's
 */
class LoginManager
{
public:

            /**
             * Log-in a user.
             * @param user User to be logged.
             * @return true on success false otherwise.
             */
            bool userLogin(User &user);

            /**
             * Log-out a user.
             * @param user User to be logged.
             * @return true on success false otherwise.
             */
            bool userLogout(User &user);

            /**
             * Adds a new user to database.
             * @param user User to be logged.
             * @return true on success false otherwise.
             */
            bool userRegister(User &user);

private:
UserDAO mUsrDAO;
};


#endif // _WS_LOGINCONTROLLER_H
