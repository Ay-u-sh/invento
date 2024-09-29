#include "../Interface/Functional/Delete.hpp"
#include "../CoreSupportModule/LibraryLoader.hpp"

typedef Delete* (__cdecl *GetDeleteInstance)();

extern "C"{
    bool erase(const unsigned char* lib_path,DatabaseHandler* db,Input* in = NULL,Output* out = NULL){
        HMODULE handle = loadLibrary(lib_path);
        if(handle){
            GetDeleteInstance get_delete_instance = reinterpret_cast<GetDeleteInstance>(GET_FUNCTION(handle,"getDeleteInstance"));
            if(get_delete_instance){
                Delete* delete_instance = get_delete_instance();
                bool result = delete_instance->remove(db,in,out);
                CLOSE_LIBRARY(handle);
                return result;
            }
        }
        CLOSE_LIBRARY(handle);
        return false;
    }
}