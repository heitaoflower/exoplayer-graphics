# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/main/cpp")
set (CONTEXT_SOURCE_DIR "${SOURCE_DIR}/context")
set (GRAPHICS_SOURCE_DIR "${SOURCE_DIR}/graphics")
set (MATH_SOURCE_DIR "${SOURCE_DIR}/math")
set (UTILS_SOURCE_DIR "${SOURCE_DIR}/utils")
set (GEOMETRY_SOURCE_DIR "${SOURCE_DIR}/geometry")
set (SENSOR_SOURCE_DIR "${SOURCE_DIR}/sensor")

SET( SOURCES

    # Root source dir.
    ${SOURCE_DIR}/exogfx_jni.c

    # Context source dir.
    ${CONTEXT_SOURCE_DIR}/context.c

    # Sensor source dir.
    ${SENSOR_SOURCE_DIR}/head_tracker.c
    ${SENSOR_SOURCE_DIR}/so3.c

    # Graphics source dir.
    ${GRAPHICS_SOURCE_DIR}/gfx.c
    ${GRAPHICS_SOURCE_DIR}/ogles_renderer.c
    ${GRAPHICS_SOURCE_DIR}/ogles_fbo.c
    ${GRAPHICS_SOURCE_DIR}/ogles_present_filter.c
    ${GRAPHICS_SOURCE_DIR}/ogles_preview_filter.c
    ${GRAPHICS_SOURCE_DIR}/ogles_gray_filter.c
    ${GRAPHICS_SOURCE_DIR}/ogles_filter_group.c

    # Utils source dir.
    ${UTILS_SOURCE_DIR}/lib_loader.c
    ${UTILS_SOURCE_DIR}/ogles_util.c
    ${UTILS_SOURCE_DIR}/math_util.c
    ${UTILS_SOURCE_DIR}/map.c
    ${UTILS_SOURCE_DIR}/vec.c

    # Geometry source dir.
    ${GEOMETRY_SOURCE_DIR}/primitive.c
    ${GEOMETRY_SOURCE_DIR}/mesh_factory.c
    ${GEOMETRY_SOURCE_DIR}/plane.c
    ${GEOMETRY_SOURCE_DIR}/quad.c
    ${GEOMETRY_SOURCE_DIR}/sphere.c

    # Math source dir.
    ${MATH_SOURCE_DIR}/camera.c
    ${MATH_SOURCE_DIR}/vec3.c
    ${MATH_SOURCE_DIR}/vec3-ext.c
    ${MATH_SOURCE_DIR}/mat3.c
    ${MATH_SOURCE_DIR}/mat4.c )

SET( HEADERS

     # Utils source dir.
     ${UTILS_SOURCE_DIR}/log_util.h
     ${UTILS_SOURCE_DIR}/ogles_util.h
     ${UTILS_SOURCE_DIR}/math_util.h
     ${UTILS_SOURCE_DIR}/lib_loader.h
     ${UTILS_SOURCE_DIR}/map.h
     ${UTILS_SOURCE_DIR}/vec.h

     # Geometry source dir.
     ${GEOMETRY_SOURCE_DIR}/primitive_type.h
     ${GEOMETRY_SOURCE_DIR}/primitive.h
     ${GEOMETRY_SOURCE_DIR}/mesh_factory.h
     ${GEOMETRY_SOURCE_DIR}/plane.h
     ${GEOMETRY_SOURCE_DIR}/quad.h
     ${GEOMETRY_SOURCE_DIR}/sphere.h

     # Math source dir.
     ${MATH_SOURCE_DIR}/camera.h
     ${MATH_SOURCE_DIR}/mat4.h
     ${MATH_SOURCE_DIR}/mat3.h
     ${MATH_SOURCE_DIR}/vec3.h
     ${MATH_SOURCE_DIR}/vec3-ext.h

     # Context source dir.
     ${CONTEXT_SOURCE_DIR}/context.h

     # Sensor source dir.
     ${SENSOR_SOURCE_DIR}/head_tracker.h
     ${SENSOR_SOURCE_DIR}/so3.h

     # Graphics source dir.
     ${GRAPHICS_SOURCE_DIR}/gfx.h
     ${GRAPHICS_SOURCE_DIR}/ogles.h
     ${GRAPHICS_SOURCE_DIR}/ogles_func.h
     ${GRAPHICS_SOURCE_DIR}/ogles_fbo.h
     ${GRAPHICS_SOURCE_DIR}/ogles_filter.h
     ${GRAPHICS_SOURCE_DIR}/ogles_present_filter.h
     ${GRAPHICS_SOURCE_DIR}/ogles_preview_filter.h
     ${GRAPHICS_SOURCE_DIR}/ogles_gray_filter.h
     ${GRAPHICS_SOURCE_DIR}/ogles_filter_group.h )

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
find_library( android-lib android )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       exogfx_jni
                       # Links the target library to the log and android libraries
                       # included in the NDK.
                       ${android-lib}
                       ${log-lib} )