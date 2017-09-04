//
// Created by showtime on 9/3/2017.
//

#include "gfx.h"
#include "load_lib.h"

#include <assert.h>

#define FNSYM(fn, ret, args) PFN_##fn fn = NULL;
#include "gl_func.h"
#undef FNSYM

static bool load_ogles_library(void)
{
    static bool loaded = false;

    static library_handle lib = NULL;

    if (loaded)
    {
        return lib != NULL;
    }

    loaded = true;

    lib = open_library("libGLESv2.so");

    if (lib == NULL)
    {
        return false;
    }

#define FNSYM(fn, ret, args)                            \
        fn = (PFN_##fn)get_library_symbol(lib, #fn);    \
        assert(fn != NULL);
#include "gl_func.h"
#undef FNSYM

    return true;
}

bool init_gfx(void)
{
    return load_ogles_library();
}
