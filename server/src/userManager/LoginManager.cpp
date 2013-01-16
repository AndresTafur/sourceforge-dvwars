#include "LoginManager.h"



bool LoginManager::userLogin(User &user)
{
       return !mUsrDAO.validate(user.getName(),user.getPassword());
}

bool LoginManager::userLogout(User &user)
{
        return !mUsrDAO.logOut( user.getName()  );
}


bool LoginManager::userRegister(User &user)
{
        return mUsrDAO.addUser( user.getName(), user.getPassword(), user.getEmail(), user.getSide());
}




