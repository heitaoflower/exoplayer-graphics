# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)


set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/main/cpp")
set (CONTEXT_SOURCE_DIR "${SOURCE_DIR}/context")
set (GRAPHICS_SOURCE_DIR "${SOURCE_DIR}/graphics")
set (GRAPHICS_OGLES_SOURCE_DIR "${GRAPHICS_SOURCE_DIR}/ogles")
set (MATH_SOURCE_DIR "${SOURCE_DIR}/math")
set (UTILS_SOURCE_DIR "${SOURCE_DIR}/utils")
set (GEOMETRY_SOURCE_DIR "${SOURCE_DIR}/geometry")
set (SENSOR_SOURCE_DIR "${SOURCE_DIR}/sensor")
set (VIDEO_SOURCE_DIR "${SOURCE_DIR}/video")

SET( SOURCES

    # Root source dir.
    ${SOURCE_DIR}/exogfx_jni.c

    # Context source dir.
    ${CONTEXT_SOURCE_DIR}/context.c

    # Sensor source dir.
    ${SENSOR_SOURCE_DIR}/head_tracker.c
    ${SENSOR_SOURCE_DIR}/so3.c
    ${SENSOR_SOURCE_DIR}/orientation_ekf.c

    # Graphics source dir.
    ${GRAPHICS_SOURCE_DIR}/gfx.c

    # Graphics ogles source dir.
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_renderer.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_eye.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_fbo.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_present_filter.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_preview_filter.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_gray_filter.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_invert_filter.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_vignette_filter.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_distortion_filter.c
    ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_effects_filter.c

    # Utils source dir.
    ${UTILS_SOURCE_DIR}/lib_loader.c
    ${UTILS_SOURCE_DIR}/ogles_util.c
    ${UTILS_SOURCE_DIR}/math_util.c

    # Geometry source dir.
    ${GEOMETRY_SOURCE_DIR}/primitive.c
    ${GEOMETRY_SOURCE_DIR}/mesh_factory.c
    ${GEOMETRY_SOURCE_DIR}/plane.c
    ${GEOMETRY_SOURCE_DIR}/quad.c
    ${GEOMETRY_SOURCE_DIR}/sphere.c
    ${GEOMETRY_SOURCE_DIR}/distortion.c

    # Math source dir.
    ${MATH_SOURCE_DIR}/camera.c
    ${MATH_SOURCE_DIR}/vec3.c
    ${MATH_SOURCE_DIR}/vec3_ext.c
    ${MATH_SOURCE_DIR}/euler.c
    ${MATH_SOURCE_DIR}/mat3.c
    ${MATH_SOURCE_DIR}/mat4.c )

SET( HEADERS

     # Utils source dir.
     ${UTILS_SOURCE_DIR}/log_util.h
     ${UTILS_SOURCE_DIR}/ogles_util.h
     ${UTILS_SOURCE_DIR}/math_util.h
     ${UTILS_SOURCE_DIR}/lib_loader.h

     # Geometry source dir.
     ${GEOMETRY_SOURCE_DIR}/primitive_type.h
     ${GEOMETRY_SOURCE_DIR}/primitive.h
     ${GEOMETRY_SOURCE_DIR}/mesh_factory.h
     ${GEOMETRY_SOURCE_DIR}/plane.h
     ${GEOMETRY_SOURCE_DIR}/quad.h
     ${GEOMETRY_SOURCE_DIR}/sphere.h
     ${GEOMETRY_SOURCE_DIR}/distortion.h

     # Math source dir.
     ${MATH_SOURCE_DIR}/camera.h
     ${MATH_SOURCE_DIR}/mat4.h
     ${MATH_SOURCE_DIR}/mat3.h
     ${MATH_SOURCE_DIR}/euler.h
     ${MATH_SOURCE_DIR}/vec3.h
     ${MATH_SOURCE_DIR}/vec3_ext.h

     # Context source dir.
     ${CONTEXT_SOURCE_DIR}/context.h

     # Sensor source dir.
     ${SENSOR_SOURCE_DIR}/head_tracker.h
     ${SENSOR_SOURCE_DIR}/so3.h
     ${SENSOR_SOURCE_DIR}/orientation_ekf.h

     # Video source dir.
     ${VIDEO_SOURCE_DIR}/video_format.h

     # Graphics source dir.
     ${GRAPHICS_SOURCE_DIR}/gfx.h

     # Graphics ogles source dir.
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_renderer.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_eye.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_func.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_fbo.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_present_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_preview_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_gray_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_invert_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_vignette_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_distortion_filter.h
     ${GRAPHICS_OGLES_SOURCE_DIR}/ogles_effects_filter.h )

#configure 3rdparty libs
set(distribution_DIR ${CMAKE_SOURCE_DIR}/../../distribution)

add_library(lib-vec STATIC IMPORTED)
set_target_properties(lib-vec PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/vec/lib/${ANDROID_ABI}/libvec.a)
add_library(lib-map STATIC IMPORTED)
set_target_properties(lib-map PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/map/lib/${ANDROID_ABI}/libmap.a)

add_library(lib-exogfx SHARED ${SOURCES} ${HEADERS})

find_library( log-lib log )
find_library( android-lib android )

target_include_directories(lib-exogfx PRIVATE
                           ${distribution_DIR}/vec/include
                           ${distribution_DIR}/map/include)

target_link_libraries(lib-exogfx
                      lib-vec
                      lib-map
                      ${android-lib}
                      ${log-lib})