#include "CSVFile.hpp"
using namespace std;    
CSVFile::CSVFile(string path):filepath(path){
    file.open(CSVFile::filepath,ios::in);
}
CSVFile::~CSVFile(){
    if(file.is_open()) file.close();
}
vector<string> CSVFile::processor(){
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
CSVFile* getCSVFileInstance(const unsigned char* path){
    return new CSVFile(reinterpret_cast<const char*>(path));
}
int main(){
    return 0;
}