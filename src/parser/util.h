#ifndef DBTRAIN_TEST_UTIL_H_
#define DBTRAIN_TEST_UTIL_H_
#include <string>
#include <fstream>
#include <iostream>

namespace dbtrain_mysql{
    enum db_data_type{
        STRING,
        INT,
        DATE
    };
    typedef db_data_type TYPE;

    const std::string DB_LIST_PATH = "../../db_list";

    class TableHead{
    public:
        std::string headName;
        TYPE type;
        TableHead(const std::string& s, const TYPE& t):headName(s), type(t){}
    };

    class Data{
    public:
        Data(){}
    };
    class Int:public Data{
    public:
        int val;
        Int(const int& i):val(i){}
    };
    class String:public Data{
    public:
        std::string val;
        String(const std::string& s):val(s){}
    };
    class Float:public Data{
    public:
        Float(const float& s):val(s){}
        float val;
    };
    class Null:public Data{
    public:
        char val = '\0';
    };
    
    
}

#endif 