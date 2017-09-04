# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/main/c")
set (GRAPHICS_SOURCE_DIR "${SOURCE_DIR}/graphics")
set (UTILS_SOURCE_DIR "${SOURCE_DIR}/utils")

SET( SOURCES

    # Root source dir.
    ${SOURCE_DIR}/exogfx_jni.c

    # Graphics source dir.
    ${GRAPHICS_SOURCE_DIR}/gfx.c
    ${GRAPHICS_SOURCE_DIR}/load_lib.c )

SET( HEADERS

     # Utils source dir.
     ${UTILS_SOURCE_DIR}/log.h

     # Graphics source dir.
     ${GRAPHICS_SOURCE_DIR}/gfx.h
     ${GRAPHICS_SOURCE_DIR}/gl.h
     ${GRAPHICS_SOURCE_DIR}/gl_func.h
     ${GRAPHICS_SOURCE_DIR}/load_lib.h )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

list(APPEND CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")

add_library( # Sets the name of the library.
             exogfx_jni

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ${SOURCES} ${HEADERS})

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( log-lib log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       exogfx_jni
                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib} )