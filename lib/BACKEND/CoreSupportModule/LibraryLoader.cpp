#include "LibraryLoader.hpp"
using namespace std;

HMODULE loadLibrary(const unsigned char* lib_path){
    string lib = reinterpret_cast<const char*>(lib_path);
    const wstring wlib(lib.begin(), lib.end());
    return LoadLibraryW(wlib.c_str());
}
int main(){
    return 0;
}