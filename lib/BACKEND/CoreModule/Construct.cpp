#include "../Interface/Functional/Create.hpp"
#include "../CoreSupportModule/LibraryLoader.hpp"

typedef Create* (__cdecl *GetCreateInstance)();

extern "C"{
    bool create(const unsigned char* lib_path,DatabaseHandler* db,Input* in = NULL,Output* out = NULL){
        HMODULE handle = loadLibrary(lib_path);
        if(handle){
            GetCreateInstance get_create_instance = reinterpret_cast<GetCreateInstance>(GetProcAddress(handle,"getCreateInstance"));
            if(get_create_instance){
                Create* create_instance = get_create_instance();
                bool result = create_instance->create(db,in,out);
                CLOSE_LIBRARY(handle);
                return result;
            }
        }
        CLOSE_LIBRARY(handle);
        return false;
    }
}