#include "UserDAO.h"

#include <iostream>

UserDAO::UserDAO()
{
    m_sqlHandler = MySQL::getInstancePtr();
}

bool UserDAO::addUser(std::string user, std::string password, std::string email, std::string idCity)
{
 Query *quer, *city;
 ResultRow fila;
 bool flag;


     city = m_sqlHandler->createQuery("select idCity from City where cityName= ':idCity' ");
     city->setParameter(":idCity",idCity);
     city->doQuery();
     idCity = city->getSingleResult()["idCity"];

     quer = m_sqlHandler->createQuery("insert into Player(username,password,email,idCity,logged) VALUES( ':user',PASSWORD(':passwd'),':email', :city,0)");
     quer->setParameter(":user",user);
     quer->setParameter(":passwd",password);
     quer->setParameter(":email",email);
     quer->setParameter(":city",idCity);

     flag = quer->execute();
     delete quer;
     return flag;
}

bool UserDAO::validate(std::string user, std::string password)
{
 Query *quer;
 ResultRow fila;
 bool flag;


     quer = m_sqlHandler->createQuery("select idPlayer from Player where username = ':user' and password = PASSWORD(':passwd')");
     quer->setParameter(":user",user);
     quer->setParameter(":passwd",password);
     quer->doQuery();

     flag = quer->getResultList().size() > 0;
     delete quer;

     if(flag)
     {
        quer = m_sqlHandler->createQuery("update Player set logged = '1' where username = ':user'");
        quer->setParameter(":user",user);
        flag = quer->execute();
        delete quer;
     }

     return flag;
}

bool UserDAO::logOut(std::string user)
{
 Query *quer;
 ResultRow fila;
 bool flag;


     quer = m_sqlHandler->createQuery("update Player set logged = '0' where idUser = ':user'");
     quer->setParameter(":user",user);
     flag = quer->execute();
     delete quer;
     return flag;
}

UserDAO::~UserDAO()
{
    //dtor
}
