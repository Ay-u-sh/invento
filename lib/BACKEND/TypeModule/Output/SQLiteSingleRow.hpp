#ifndef Single_Row_SQLite_H
#define Single_Row_SQLite_H

#include "../../Interface/Types/Output.hpp"
#include<string>

class SQLiteSingleRow : public Output{
    public:
        std::string result_row_set;
};
extern "C"{
    SQLiteSingleRow* getLiteSingleRowInstance();
}

#endif