#include "SQLiteSingleRowStruct.hpp"

SQLiteSingleRowStruct* getStruct(SQLiteSingleRow* sqlite) {
    SQLiteSingleRowStruct* ssrs_struct = new SQLiteSingleRowStruct;
    ssrs_struct->row = new unsigned char[sqlite->result_row_set.size()];
    strcpy((char*)ssrs_struct->row,sqlite->result_row_set.c_str());
    return ssrs_struct;
}