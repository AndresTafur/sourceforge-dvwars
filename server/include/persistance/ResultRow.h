#ifndef _RESULT_ROW_H_
#define _RESULT_ROW_H_

#include <map>
#include <string>

/**
 * Encapsulates a database register
 **/
class ResultRow
{
public:

    /**
     * adds new column to this register
     */
    void addResult(std::string col, std::string val);

    /**
     * Access register information.
     * @param col colId.
     */
    std::string operator [](std::string col);

private:
std::map<std::string,std::string> m_list;
};

#endif
