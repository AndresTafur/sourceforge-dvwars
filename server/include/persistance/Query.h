#ifndef _QUERY_H_
#define _QUERY_H_

#include <mysql/mysql.h>
#include <vector>

#include "ResultRow.h"
#include "DBException.h"

/**
 * Represents a query
 */
class Query
{
protected:

        /**
         * Constructor, allow creation only to MySQL
         * @param handler MYSQL handler.
         * @param query   Query to be executed.
         */
        Query(MYSQL *handler,std::string query);

public:

    void doQuery();

    bool execute();

    /**
     * Sets the arguments of a parametrized query
     * @param param Parameter to set a value.
     * @param value Value to be set.
     */
    void setParameter(std::string param, std::string value);

    /**
     * Obtains a list of results.
     * @return ResultRow list
     * @see ResultRow
     */
    std::vector<ResultRow> getResultList();

    /**
     * Obtains a single (or first) result
     * @return result obtained
     * @see ResultRow.
     */
    ResultRow getSingleResult();

    inline std::string getQuery() { return m_query;}

private:
std::string m_query;
MYSQL_RES  *m_resultSet;
MYSQL      *m_handler;
std::vector<ResultRow> m_rows;

friend class MySQL;
};
#endif
