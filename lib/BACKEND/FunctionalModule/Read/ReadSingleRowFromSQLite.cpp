#include"ReadSingleRowFromSQLite.hpp"
#include<iostream>
using namespace std;

bool ReadSingleRowFromSQLite::read(DatabaseHandler* db,Input* in,Output* out){
    SQLite* sqlite = (SQLite*)(db);
    SQLiteSingleRow* output = (SQLiteSingleRow*)(out);
    vector<string> result = sqlite->getData();
    
    output->result_row_set = dataParser(result,"|");
    return true;
}

string ReadSingleRowFromSQLite::dataParser(vector<string> data,string separator){
    string result = "";
    if(!data.empty()){
        for(int i=0;i<data.size()-1;i++)
            result += data[i] + separator;
        result += data.back();
    }
    return result.empty()?separator:result;
}
Read* getReadInstance(){
    return new ReadSingleRowFromSQLite();
}
int main(){
    return 0;
}