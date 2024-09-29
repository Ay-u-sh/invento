#ifndef INS_CSV_IN_SQL_H
#define INS_CSV_IN_SQL_H

#include "../../Interface/Functional/Insert.hpp"
#include "../../TypeModule/Input/File/CSVFile.hpp"
#include "../../TypeModule/Database/SQLite.hpp"
#include "../../SupportModule/InventoryData.hpp"

class InsertCSVInSQLite:public Insert{
    public:
        bool insert(DatabaseHandler*,Input*,Output*) override;
        bool add(CSVFile*,SQLite*);
};

#endif