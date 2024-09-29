#if defined(_WIN32)
#include <windows.h>
#define LIB_HANDLE HMODULE
#define OPEN_LIBRARY(file) LoadLibraryW(file)
#define CLOSE_LIBRARY(handle) FreeLibrary(handle)
#define GET_FUNCTION(handle, name) GetProcAddress(handle, name)
#else
#include <dlfcn.h>
#define LIB_HANDLE void*
#define OPEN_LIBRARY(file) dlopen(file, RTLD_LAZY)
#define CLOSE_LIBRARY(handle) dlclose(handle)
#define GET_FUNCTION(handle, name) dlsym(handle, name)
#endif
#include<string>

HMODULE loadLibrary(const unsigned char*);

void unloadLibrary(HMODULE);
