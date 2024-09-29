#include "../Interface/Functional/Read.hpp"
#include "../CoreSupportModule/LibraryLoader.hpp"

typedef Read* (__cdecl *GetReadInstance)();

extern "C"{
    bool read(const unsigned char* lib_path,DatabaseHandler* db,Input* in = NULL,Output* out = NULL){
        HMODULE handle = loadLibrary(lib_path);
        if(handle){
            GetReadInstance get_read_instance = reinterpret_cast<GetReadInstance>(GET_FUNCTION(handle,"getReadInstance"));
            if(get_read_instance){
                Read* read_instance = get_read_instance();
                bool result = read_instance->read(db,in,out);
                CLOSE_LIBRARY(handle);
                return result;
            }
        }
        CLOSE_LIBRARY(handle);
        return false;
    }
}