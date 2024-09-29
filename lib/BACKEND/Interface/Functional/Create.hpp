#ifndef CREATE_H
#define CREATE_H
#ifdef DLL_API
    #define DLL_API __declspec(dllexport)
#else
    #define DLL_API __declspec(dllimport)
#endif

#include "../Types/Input.hpp"
#include "../Types/Output.hpp"
#include "../Types/DatabaseHandler.hpp"

class Create{
    public:
        virtual bool create(DatabaseHandler*,Input* = nullptr,Output* = nullptr) = 0;
        virtual ~Create() = default;
};


extern "C"{
    Create* getCreateInstance();
}
#endif