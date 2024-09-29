#include "InventoryData.hpp"
using namespace std;
bool InventoryData::organizeData(vector<string>& data){
    if(data.size()!=capacity)
        return false;
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
string InventoryData::getDataValue(){
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
int InventoryData::getSize(){
    return capacity;
}
int main(){
    return 0;
}