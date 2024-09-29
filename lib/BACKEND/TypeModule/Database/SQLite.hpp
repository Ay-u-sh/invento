#ifndef SQLITE_H
#define SQLITE_H

#include "../../Interface/Types/DatabaseHandler.hpp"
#include "../../SupportModule/InventoryData.hpp"
#include "../../CoreSupportModule/sqlite3.h"

#include<vector>

class SQLite : public DatabaseHandler{
    private:
        sqlite3* con;
        const std::string table_name;
        std::string db_file_name;

        sqlite3_stmt* get_insert_data_stmt_state;
        sqlite3_stmt* get_data_stmt_state;
        sqlite3_stmt* get_top_selling_stmt_state;
        sqlite3_stmt* get_low_stock_stmt_state; 

        bool prepareQuery(std::string &,sqlite3_stmt* &);
        bool processInsertData(std::vector<InventoryData*> &);
        bool processResultData(std::vector<std::string> &,sqlite3_stmt* &);
    public:
        SQLite(const std::string&,const std::string &);
        std::vector<std::string> getData();
        bool insertData(std::vector<InventoryData*>);
        ~SQLite();
};
extern "C"{
    SQLite* getSQLiteInstance(const unsigned char* db_file_name,const unsigned char* table_name);
}
#endif