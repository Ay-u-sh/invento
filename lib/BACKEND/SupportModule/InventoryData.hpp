#ifndef INVENTORYDATA_H
#define INVENTORYDATA_H

#include "../Interface/Types/Input.hpp"
#include<string>
#include<vector>

class InventoryData:public Input{
    private:
        int ID;
        std::string PRODUCTNAME;
        int PRICE;
        std::string BRAND;
        int QUANTITY;
        int capacity=5;
    public:
        bool organizeData(std::vector<std::string>&);
        std::string getDataValue();
        int getSize();
};
#endif