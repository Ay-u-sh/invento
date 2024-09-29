#ifndef Read_Single_Row_SQLite_H
#define Read_Single_Row_SQLite_H

#include "../../Interface/Functional/Read.hpp"
#include "../../TypeModule/Database/SQLite.hpp"
#include "../../TypeModule/Output/SQLiteSingleRow.hpp"
#include<vector>

class ReadSingleRowFromSQLite:public Read{
    private:
        std::string dataParser(std::vector<std::string> data,std::string separator);
    public:
        bool read(DatabaseHandler*,Input*,Output*) override;
};

#endif