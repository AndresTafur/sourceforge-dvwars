#include "MySQL.h"


MySQL * MySQL::sm_instance = 0;


MySQL::MySQL()
{
    m_handler = mysql_init(0);

    if(!m_handler)
        throw DBException("Failed to initilize mysql");
}



MySQL* MySQL::getInstancePtr()
{

    if(!sm_instance)
        sm_instance = new MySQL();

    return sm_instance;
}


bool MySQL::connect(std::string user, std::string password, const char *database, std::string server, int port)
{
  bool ret = false;


        ret = mysql_real_connect(m_handler, server.c_str(), user.c_str(), password.c_str(), database, port, NULL, 0) != NULL;

        return ret;
}


Query* MySQL::createQuery(std::string query)
{
Query *obj = new Query(m_handler,query);

 return obj;
}



void MySQL::destroy()
{
 mysql_close(m_handler);
}
