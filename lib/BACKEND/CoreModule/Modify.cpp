#include "../Interface/Functional/Update.hpp"
#include "../CoreSupportModule/LibraryLoader.hpp"

typedef Update* (__cdecl *GetUpdateInstance)();

extern "C"{
    bool update(const unsigned char* lib_path,DatabaseHandler* db,Input* in = NULL,Output* out = NULL){
        HMODULE handle = loadLibrary(lib_path);
        if(handle){
            GetUpdateInstance get_update_instance = reinterpret_cast<GetUpdateInstance>(GET_FUNCTION(handle,"getUpdateInstance"));
            if(get_update_instance){
                Update* update_instance = get_update_instance();
                bool result = update_instance->update(db,in,out);
                CLOSE_LIBRARY(handle);
                return result;
            }
        }
        CLOSE_LIBRARY(handle);
        return false;
    }
}