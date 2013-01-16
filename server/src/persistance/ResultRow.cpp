#include "ResultRow.h"
#include <stdio.h>

    void ResultRow::addResult(std::string col, std::string val)
    {
       fprintf(stderr,"ResultSet %s : %s\n",col.c_str(),val.c_str());
       m_list.insert( std::make_pair(col,val)  );
    }

    std::string ResultRow::operator [](std::string col)
    {
        return m_list[col];
    }

