//
// Created by showtime on 9/3/2017.
//
#include "lib_loader.h"

#include <stdio.h>

library_handle open_library(const char *lib)
{
    return dlopen(lib, RTLD_NOW);
}

void close_library(library_handle lib)
{
    dlclose(lib);
}

void* get_library_symbol(library_handle lib, const char *fn)
{
    if (lib)
    {
        return dlsym(lib, fn);
    }

    return NULL;
}
