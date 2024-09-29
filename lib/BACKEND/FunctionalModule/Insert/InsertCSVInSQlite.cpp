#include "InsertCSVInSQlite.hpp"
using namespace std;

bool InsertCSVInSQLite::add(CSVFile* csv,SQLite* sqlite){
    vector<string> result;
    vector<InventoryData*> data;
    
    while(!(result = csv->processor()).empty()){
        InventoryData* inventory_data = new InventoryData();
        if(inventory_data->organizeData(result))
            data.push_back(inventory_data);
        else{
            for(int i=0;i<data.size();i++)
                delete data[i];
            data.clear();
            return false;
        }
    }

    if(!sqlite->insertData(data)) return false;
    for(int i=0;i<data.size();i++){
        delete data[i];
    }
    
    data.clear();
    return true;
}
bool InsertCSVInSQLite::insert(DatabaseHandler* db,Input* in,Output* out){
    CSVFile* csv_file = (CSVFile*)in;
    SQLite* sqlite_handler = (SQLite*)db;

    if(csv_file && sqlite_handler){
        return InsertCSVInSQLite::add(csv_file,sqlite_handler); 
    }
    return false;
}
DLL_API Insert* getInsertInstance(){
    return new InsertCSVInSQLite();
}
int main(){
    return 0;
}