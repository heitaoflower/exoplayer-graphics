//
// Created by showtime on 9/3/2017.
//

#ifndef EXOPLAYER_UTILS_LOAD_LIB_H
#define EXOPLAYER_UTILS_LOAD_LIB_H

#include <dlfcn.h>

typedef  void* library_handle;

library_handle open_library(const char *lib);

void* get_library_symbol(library_handle lib, const char * fn);

#endif //EXOPLAYER_UTILS_LOAD_LIB_H
