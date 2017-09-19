//
// Created by showtime on 9/3/2017.
//

#ifndef EXOGFX_UTILS_LIB_LOADER_H
#define EXOGFX_UTILS_LIB_LOADER_H

#include <dlfcn.h>

typedef  void* library_handle;

library_handle open_library(const char *lib);

void* get_library_symbol(library_handle lib, const char * fn);

#endif //EXOGFX_UTILS_LIB_LOADER_H
