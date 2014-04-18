#include <stdlib.h>
#include <dlfcn.h>


Dl_info _so_info;

//! This function is called when the shared object (DLL) is initially loaded.
__attribute__((constructor))
void hosslib_load(void)
{
}

//! This function is called when the shared object (DLL) is unloaded.
__attribute__((constructor))
void hosslib_unload(void)
{

}


