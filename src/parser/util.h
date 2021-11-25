#ifndef DBTRAIN_TEST_UTIL_H_
#define DBTRAIN_TEST_UTIL_H_
#include <string>

namespace dbtrain_mysql{
    enum db_data_type{
        STRING,
        INT,
        DATE
    };
    typedef db_data_type TYPE;



    class TableHead{
    public:
        std::string headName;
        TYPE type;
        TableHead(const std::string& s, const TYPE& t):headName(s), type(t){}
    };
}
#endif 