#ifndef CSVFILE_H
#define CSVFILE_H
#include "../../../Interface/Types/Input.hpp"
#include<fstream>
#include<vector>
class CSVFile:public Input{
    private:
        std::string filepath;
        std::fstream file;
    public:
        CSVFile(std::string);
        std::vector<std::string> processor();
        ~CSVFile();
};
extern "C"{
    CSVFile* getCSVFileInstance(const unsigned char*);
}
#endif