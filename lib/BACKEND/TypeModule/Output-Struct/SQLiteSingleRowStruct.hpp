#ifndef Lite_Single_Row_Struct
#define Lite_Single_Row_Struct

#include "../Output/SQLiteSingleRow.hpp"
#include <cstring>

struct SQLiteSingleRowStruct {
    unsigned char* row;
};

extern "C" SQLiteSingleRowStruct* getStruct(SQLiteSingleRow* sqlite);

#endif