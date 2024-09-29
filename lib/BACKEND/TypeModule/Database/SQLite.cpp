#include "SQLite.hpp"
using namespace std;
bool SQLite::prepareQuery(string &query,sqlite3_stmt* &stmt_state){
    if(stmt_state == NULL){
        if(sqlite3_prepare_v2(con,query.c_str(),-1,&stmt_state,NULL) == SQLITE_OK) return true;
        else{
            sqlite3_finalize(stmt_state);
            stmt_state = NULL;
            return false;
        }
    }
    return true;
}

bool SQLite::processInsertData(vector<InventoryData*> &data){
    int result_code;
    for(int i = 0;i<data.size();i++){
        sqlite3_bind_int(get_insert_data_stmt_state,1,stoi(data[i]->getDataValue()));
        
        sqlite3_bind_text(get_insert_data_stmt_state,2,data[i]->getDataValue().c_str(),-1,SQLITE_STATIC);
        
        sqlite3_bind_int(get_insert_data_stmt_state,3,stoi(data[i]->getDataValue()));
        
        sqlite3_bind_text(get_insert_data_stmt_state,4,data[i]->getDataValue().c_str(),-1,SQLITE_STATIC);
        
        sqlite3_bind_int(get_insert_data_stmt_state,5,stoi(data[i]->getDataValue()));
        
        result_code = sqlite3_step(get_insert_data_stmt_state);

        sqlite3_clear_bindings(get_insert_data_stmt_state);
        sqlite3_reset(get_insert_data_stmt_state);

        if(result_code != SQLITE_DONE)
            return false;
    }
    return true;
}

bool SQLite::processResultData(vector<string> &data,sqlite3_stmt* &stmt_state){
    int result_code = sqlite3_step(stmt_state);

    if(result_code == SQLITE_ROW){
        data.push_back(to_string(sqlite3_column_int(stmt_state,0)));

        data.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt_state,1)));
        
        data.push_back(to_string(sqlite3_column_int(stmt_state,2)));
        
        data.push_back(reinterpret_cast<const char*>(sqlite3_column_text(stmt_state,3)));
        
        data.push_back(to_string(sqlite3_column_int(stmt_state,4)));
    }
    else if(result_code == SQLITE_DONE)
        sqlite3_reset(stmt_state);
    else{
        sqlite3_reset(stmt_state);
        return false; 
    }  
    return true;
}
SQLite::SQLite(const string &db_file_name,const string &table_name):table_name(table_name),db_file_name(db_file_name){
    if(sqlite3_open(db_file_name.c_str(),&con) == SQLITE_OK);
    else{
        sqlite3_close(con);
        con = NULL;
    }
    get_insert_data_stmt_state = NULL;
    get_data_stmt_state = NULL;
    get_top_selling_stmt_state = NULL;
    get_low_stock_stmt_state = NULL;
}
SQLite::~SQLite(){
    sqlite3_finalize(get_insert_data_stmt_state);
    sqlite3_finalize(get_data_stmt_state);
    sqlite3_finalize(get_top_selling_stmt_state);
    sqlite3_finalize(get_low_stock_stmt_state);
    sqlite3_close(con);
    
    con = NULL;
    get_insert_data_stmt_state = NULL;
    get_data_stmt_state = NULL;
    get_low_stock_stmt_state = NULL;
    get_top_selling_stmt_state = NULL;
}
bool SQLite::insertData(vector<InventoryData*> data){
    string query = "INSERT INTO "+ table_name + " VALUES(?,?,?,?,?)";
    
    bool result_code_prepare = prepareQuery(query,get_insert_data_stmt_state);
    bool result_process_data;

    if(!result_code_prepare || !(result_process_data = processInsertData(data)))
        return false;
    
    return true;
}
vector<string> SQLite::getData(){
    vector<string> data;

    string query = "SELECT * FROM "+ table_name;

    if(!prepareQuery(query,get_data_stmt_state)) return data;

    processResultData(data,get_data_stmt_state);
    
    return data;
}
SQLite* getSQLiteInstance(const unsigned char* db_file_name,const unsigned char* table_name){
    return new SQLite(reinterpret_cast<const char*>(db_file_name),reinterpret_cast<const char*>(table_name));
}
int main(){
    return 0;
}