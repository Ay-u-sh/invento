#include "../Interface/Functional/Insert.hpp"
#include "../CoreSupportModule/LibraryLoader.hpp"

typedef Insert* (__cdecl *GetInsertInstance)();

extern "C"{
    bool pushData(const unsigned char* lib_path,DatabaseHandler* db,Input* in=NULL,Output* out=NULL){
        HMODULE handle = loadLibrary(lib_path);
        if(handle){
            GetInsertInstance get_insert_instance = reinterpret_cast<GetInsertInstance>(GET_FUNCTION(handle, "getInsertInstance"));
            if(get_insert_instance){
                Insert* insert_instance = get_insert_instance();
                bool result = insert_instance->insert(db,in,out);
                CLOSE_LIBRARY(handle);
                return result;
            }
        }
        CLOSE_LIBRARY(handle);
        return false;
    }
}
int main(){
    return 0;
}