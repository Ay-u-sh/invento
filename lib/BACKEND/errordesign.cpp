#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include"sqlite3.h"
using namespace std;

class StructuredData{
    public:
        virtual bool organizeData(vector<string> data) = 0;
        virtual string getDataValue() = 0;
        virtual int getSize() = 0;
        virtual ~StructuredData() = default;
};
class InventoryData : public StructuredData{
    private:
        int ID;
        string PRODUCTNAME;
        int PRICE;
        string BRAND;
        int QUANTITY;
        int capacity = 5;
    public:
        bool organizeData(vector<string> data){
            if(data.size()!=capacity){
                cout<<"Structured Data capacity not equal to data.size()"<<endl;
                return false;
            }
            for(int i = 0;i<data.size();i++){
                switch(i){
                    case 0:
                        ID = stoi(data[i]);
                        break;
                    case 1:
                        PRODUCTNAME = data[i];
                        break;
                    case 2:
                        PRICE = stoi(data[i]);
                        break;
                    case 3:
                        BRAND = data[i];
                        break;
                    case 4:
                        QUANTITY = stoi(data[i]);
                        break;
                    default:
                        return false;
                }
            }
            return true;
        }
        string getDataValue(){
            capacity--;
            switch(capacity){
                case 4:
                    return to_string(ID);
                case 3:
                    return PRODUCTNAME;
                case 2:
                    return to_string(PRICE);
                case 1:
                    return BRAND;
                case 0:
                    return to_string(QUANTITY);
                default:
                    capacity = 5;
                    return "";
            }
            return "";
        }
        int getSize(){
            return capacity;
        }
};

class FileParser{
    public:
        virtual vector<string> processor() = 0;
        virtual ~FileParser() = default;
};
class CSVFileParser : public FileParser{
    private:
        const string file_name;
        fstream file;
    public:
        CSVFileParser(const string name):file_name(name){
            file.open(file_name,ios::in);
            if(!file.is_open()) cout<<"cannot open file"<<endl;
        }
        ~CSVFileParser(){
            if(file.is_open()) file.close();
        }
        vector<string> processor(){
            vector<string> result;
            char character_value;
            string field_value = "";

            while(file.get(character_value) && character_value != '\n'){
                if(character_value != ',')
                    field_value.push_back(character_value);
                else{
                    result.push_back(field_value);
                    field_value.clear();
                }
            }
            if(!field_value.empty())
                result.push_back(field_value);
            return result;
        }
};

class DatabaseHandler{
    public:
        virtual bool insertData(vector<StructuredData*> data) = 0;
        virtual vector<string> getData() = 0;
        virtual vector<string> getTopSelling() = 0;
        virtual vector<string> getLowStock(int) = 0;
        virtual ~DatabaseHandler() = default;
};
class SQLiteHandler : public DatabaseHandler{
    private:
        sqlite3* con;
        const string table_name;
        string db_file_name;

        sqlite3_stmt* get_insert_data_stmt_state;
        sqlite3_stmt* get_data_stmt_state;
        sqlite3_stmt* get_top_selling_stmt_state;
        sqlite3_stmt* get_low_stock_stmt_state;  

        bool prepareQuery(string &query,sqlite3_stmt* &stmt_state){
            if(stmt_state == NULL){
                if(sqlite3_prepare_v2(con,query.c_str(),-1,&stmt_state,NULL) == SQLITE_OK) return true;
                else{
                    cout<<sqlite3_errmsg(con)<<endl;
                    sqlite3_finalize(stmt_state);
                    stmt_state = NULL;
                    return false;
                }
            }
            return true;
        }

        bool processInsertData(vector<StructuredData*> &data){
            int result_code;
            for(int i = 0;i<data.size();i++){
                int id = stoi(data[i]->getDataValue());
                string name = data[i]->getDataValue();
                int price = stoi(data[i]->getDataValue());
                string brand = data[i]->getDataValue();
                int quantity = stoi(data[i]->getDataValue());
                cout<<id<<"|"<<name<<"|"<<price<<"|"<<brand<<"|"<<quantity<<endl;
                if(sqlite3_bind_int(get_insert_data_stmt_state,1,id) != SQLITE_OK) cout<<sqlite3_errmsg(con)<<endl;
                
                if(sqlite3_bind_text(get_insert_data_stmt_state,2,name.c_str(),-1,SQLITE_STATIC) != SQLITE_OK) cout<<sqlite3_errmsg(con)<<endl;
                
                if(sqlite3_bind_int(get_insert_data_stmt_state,3,price) != SQLITE_OK) cout<<sqlite3_errmsg(con)<<endl;
                
                if(sqlite3_bind_text(get_insert_data_stmt_state,4,brand.c_str(),-1,SQLITE_STATIC) != SQLITE_OK) cout<<sqlite3_errmsg(con)<<endl;
                
                if(sqlite3_bind_int(get_insert_data_stmt_state,5,quantity) != SQLITE_OK) cout<<sqlite3_errmsg(con)<<endl;
               
                result_code = sqlite3_step(get_insert_data_stmt_state);
                cout<<"iteration->"<<i<<"result code ->"<<result_code<<endl;
                
                sqlite3_clear_bindings(get_insert_data_stmt_state);
                sqlite3_reset(get_insert_data_stmt_state);

                if(result_code != SQLITE_DONE){
                    cout<<sqlite3_errmsg(con)<<endl;
                    return false;
                }
            }
            return true;
        }

        bool processResultData(vector<string> &data,sqlite3_stmt* &stmt_state){
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
                cout<<"result_code:"<<result_code<<" "<<"sqlitedone:"<<SQLITE_DONE<<" "<<"sqliterow:"<<SQLITE_ROW<<endl;
                cout<<sqlite3_errmsg(con)<<endl;
                sqlite3_reset(stmt_state);
            }
            return true;
        }

    public:
        SQLiteHandler(const string db_file_name,const string table_name):table_name(table_name),db_file_name(db_file_name){
            if(sqlite3_open(db_file_name.c_str(),&con) == SQLITE_OK);
            else{
                cout<<sqlite3_errmsg(con);
                sqlite3_close(con);
                con = NULL;
            }
            get_insert_data_stmt_state = NULL;
            get_data_stmt_state = NULL;
            get_top_selling_stmt_state = NULL;
            get_low_stock_stmt_state = NULL;
        }
        ~SQLiteHandler(){
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

        bool insertData(vector<StructuredData*> data){
            string query = "INSERT INTO "+ table_name + " VALUES(?,?,?,?,?)";
            
            bool result_code_prepare = prepareQuery(query,get_insert_data_stmt_state);
            bool result_process_data;
            
            if(!result_code_prepare) cout<<sqlite3_errmsg(con)<<endl;
            if(!(result_process_data = processInsertData(data))){
                cout<<"Process Insert Data Failed"<<endl;
                return false;
            }
    
            sqlite3_reset(get_data_stmt_state);
            return true;
        }

        vector<string> getData(){
            vector<string> data;

            string query = "SELECT * FROM "+ table_name;

            if(!prepareQuery(query,get_data_stmt_state)) return data;

            if(!processResultData(data,get_data_stmt_state)) cout<<"error in process result data getData()"<<endl;
            
            return data;
        }

        vector<string> getTopSelling(){
            vector<string> data;
            string query = "SELECT ID,PRODUCTNAME,PRICE,BRAND,SUM(QUANTITY) FROM PRODUCT GROUP BY PRODUCTNAME ORDER BY QUANTITY DESC";

            if(!prepareQuery(query,get_top_selling_stmt_state)) return data;
            
            if(!processResultData(data,get_top_selling_stmt_state)) cout<<"error in process result data getTopSelling()"<<endl;  
        
            return data;
        }

        vector<string> getLowStock(int limit){
            vector<string> data;
            string query = "SELECT * FROM PRODUCT WHERE QUANTITY <= " + to_string(limit) + " ORDER BY QUANTITY";
        
            if(!prepareQuery(query,get_low_stock_stmt_state)) return data;

            if(!processResultData(data,get_low_stock_stmt_state)) cout<<"error in process result data getLowStock()"<<endl;
    
            return data;
        }
};
FileParser* openCSVFile(const string file_name){
    return new CSVFileParser(file_name);
}
vector<string> parseCSVFile(FileParser* fp){
    return fp->processor();
}
bool closeCSVFile(FileParser* fp){
    delete fp;
    fp = NULL;
    return true;
}

unsigned char* commonDataParser(vector<string> data,unsigned char* separator){
    string result = "";
    string sep = reinterpret_cast<const char*>(separator);
    if(!data.empty()){
        for(int i=0;i<data.size()-1;i++)
            result += data[i] + sep;
        result += data.back();
    }
    unsigned char* sqlite_data = new unsigned char[result.length()+1];
    strcpy((char*)sqlite_data,result.c_str());// make your own strcpy it can be done and remove cstring.h
    return result.empty()?separator:sqlite_data;
}

extern "C"{

    DatabaseHandler* getSQLiteConnection(const unsigned char* db_file_name,const unsigned char* table_name){
        return new SQLiteHandler(reinterpret_cast<const char*>(db_file_name),reinterpret_cast<const char*>(table_name));
    }

    bool insertCSVSqlite(const unsigned char* file_name,const unsigned char* db_file_name,const unsigned char* table_name){
        FileParser* fp = openCSVFile(reinterpret_cast<const char*>(file_name));
        
        vector<string> result;
        vector<StructuredData*> data;
        while(!(result = fp->processor()).empty()){
            StructuredData* sd = new InventoryData();
            if(sd->organizeData(result))
                data.push_back(sd);
            else{
                for(int i=0;i<data.size();i++)
                    delete data[i];
                data.clear();
                return false;
            }
        }
        cout<<"Parsed csv objects size : "<<data.size()<<endl;
        DatabaseHandler* db_handler = new SQLiteHandler(reinterpret_cast<const char*>(db_file_name),reinterpret_cast<const char*>(table_name));
        if(!db_handler->insertData(data)){
            cout<<"Data Insertion failed"<<endl;
            return false;
        }
        for(int i=0;i<data.size();i++){
            delete data[i];
            data.clear();
        }
        return true;
    }

    unsigned char* getTableData(DatabaseHandler* db_handler,unsigned char* separator){
        vector<string> data = db_handler->getData();
        return commonDataParser(data,separator);
    }
    
    unsigned char* getTopSellingData(DatabaseHandler* db_handler,unsigned char* separator){
        vector<string> data = db_handler->getTopSelling();
        return commonDataParser(data,separator);
    }

    unsigned char* getLowStockData(DatabaseHandler* db_handler,int limit,unsigned char* separator){
        vector<string> data = db_handler->getLowStock(limit);
        return commonDataParser(data,separator);
    }

    DatabaseHandler* closeSQLiteConnection(DatabaseHandler* db_handler){
        delete db_handler;
        db_handler = NULL;
        return NULL;
    }
}

int main(){
    return 0;
}