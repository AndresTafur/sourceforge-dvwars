#ifndef _PA_MYSQL_H_
#define _PA_MYSQL_H_

#include <string>
#include "Query.h"
#include "DBException.h"

/**
 * Encapsulate the mysql connection.
 */
class MySQL
{
protected:

            MySQL();

public:

            static MySQL* getInstancePtr();

            bool connect(std::string user, std::string password, const char *database = NULL, std::string server = "localhost", int port = 3306);

            /**
             * Creates a new string based query.
             * @param query Query to be created.
             */
            Query* createQuery(std::string query);

            void destroy();

private:
MYSQL *m_handler;
static MySQL *sm_instance;
};
#endif
