#ifndef INSERT_H
#define INSERT_H
#ifdef DLL_API
    #define DLL_API __declspec(dllimport)
#else
    #define DLL_API __declspec(dllexport)
#endif

#include "../Types/Input.hpp"
#include "../Types/Output.hpp"
#include "../Types/DatabaseHandler.hpp"
class Insert{
    public:
        virtual bool insert(DatabaseHandler*,Input* = nullptr,Output* = nullptr) = 0;
        virtual ~Insert() = default;
};
extern "C"{
    Insert* getInsertInstance();
}
#endif