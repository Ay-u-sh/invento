#ifndef DELETE_H
#define DELETE_H
#ifdef DLL_API
    #define DLL_API __declspec(dllexport)
#else
    #define DLL_API __declspec(dllimport)
#endif

#include "../Types/Input.hpp"
#include "../Types/Output.hpp"
#include "../Types/DatabaseHandler.hpp"

class Delete{
    public:
        virtual bool remove(DatabaseHandler*,Input* = nullptr,Output* = nullptr) = 0;
        virtual ~Delete() = default;
};

extern "C"{
    Delete* getDeleteInstance();
}
#endif