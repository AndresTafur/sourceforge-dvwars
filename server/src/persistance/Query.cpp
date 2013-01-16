#include "Query.h"
#include <stdio.h>


    Query::Query(MYSQL *handler,std::string query)
    {
        m_handler = handler;
        m_query = query;
    }

    void Query::doQuery()
    {
      int rows, cols;
      MYSQL_FIELD *columnNames;
      MYSQL_RES *res;
      MYSQL_ROW row;


            mysql_query(m_handler, m_query.c_str());
            res = mysql_store_result(m_handler);

           if(res)
            {
                    rows = (int) mysql_num_rows(res);
                    cols = (int) mysql_num_fields(res);

                    columnNames = mysql_fetch_fields(res);

                    for(int l = 0; l < rows; l++)
                    {
                        ResultRow rRow;

                                row = mysql_fetch_row(res);

                                for(int k = 0 ; k < cols ; k++)
                                    rRow.addResult(columnNames[k].name, ((row[k]==NULL) ? "NULL" : row[k]) );

                                m_rows.push_back(rRow);
                    }
            }
            else
            throw DBException( mysql_error(m_handler) );
    }

    bool Query::execute()
    {
        return !mysql_query(m_handler, m_query.c_str());
    }


     void Query::setParameter(std::string param, std::string value)
     {
       int iter;

                iter = m_query.find(param);
                m_query.replace(iter,param.length(),value);
     }


     std::vector<ResultRow> Query::getResultList()
     {
        return m_rows;
     }

    ResultRow Query::getSingleResult()
    {
        return m_rows.at(0);
    }

