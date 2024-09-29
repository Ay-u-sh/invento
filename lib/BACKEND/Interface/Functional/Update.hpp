#ifndef UPDATE_H
#define UPDATE_H

#ifdef DLL_API
    #define DLL_API __declspec(dllexport)
#else
    #define DLL_API __declspec(dllimport)
#endif

#include "../Types/Input.hpp"
#include "../Types/Output.hpp"
#include "../Types/DatabaseHandler.hpp"

class Update{
    public:
        virtual bool update(DatabaseHandler*,Input* = nullptr,Output* = nullptr);
        virtual ~Update() = 0;
};
extern "C"{
    Update* getUpdateInstance();
}
#endif