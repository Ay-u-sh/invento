#ifndef READ_H
#define READ_H
#ifdef DLL_API
    #define DLL_API __declspec(dllimport)
#else
    #define DLL_API __declspec(dllexport)
#endif

#include "../Types/Input.hpp"
#include "../Types/Output.hpp"
#include "../Types/DatabaseHandler.hpp"

class Read{
    public:
        virtual bool read(DatabaseHandler*,Input* = nullptr,Output* = nullptr) = 0;
        virtual ~Read() = default;
};

extern "C"{
    Read* getReadInstance();
}

#endif