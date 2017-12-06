//
// Created by showtime on 12/4/2017.
//
#include "euler.h"
#include "mat4.h"

#include <math.h>

void euler_angles(mat4 *src, struct vec3 *dst)
{
    if (*mat4_element(src, 0, 2) < 1.0f) {
        if (*mat4_element(src, 0, 2) > -1.0f) {
            struct vec3  a[2];
            float cy1, cy2;
            int   path;

            a[0].y = asinf(-*mat4_element(src, 0, 2));
            a[1].y = PI_2 - a[0].y;

            cy1 = cosf(a[0].y);
            cy2 = cosf(a[1].y);

            a[0].x = atan2f(*mat4_element(src, 1, 2) / cy1, *mat4_element(src, 2, 2) / cy1);
            a[1].x = atan2f(*mat4_element(src, 1, 2) / cy2, *mat4_element(src, 2, 2) / cy2);

            a[0].z = atan2f(*mat4_element(src, 0, 1) / cy1, *mat4_element(src, 0, 0) / cy1);
            a[1].z = atan2f(*mat4_element(src, 0, 1) / cy2, *mat4_element(src, 0, 0) / cy2);

            path = (fabsf(a[0].x) + fabsf(a[0].y) + fabsf(a[0].z)) >=
                   (fabsf(a[1].x) + fabsf(a[1].y) + fabsf(a[1].z));

            vec3_copy(&a[path], dst);
        } else {
            dst->x = atan2f(*mat4_element(src, 1, 0), *mat4_element(src, 2, 0));
            dst->y = PI_2;
            dst->z = 0.0f;
        }
    } else {
        dst->x = atan2f(-*mat4_element(src, 1, 0), -*mat4_element(src, 2, 0));
        dst->y =-PI_2;
        dst->z = 0.0f;
    }
}

void euler_xyz(struct vec3 *angles, mat4 *dst)
{
    float cx, cy, cz, sx, sy, sz;

    sx = sinf(angles->x); cx = cosf(angles->x);
    sy = sinf(angles->y); cy = cosf(angles->y);
    sz = sinf(angles->z); cz = cosf(angles->z);

    *mat4_element(dst, 0, 0) = cy * cz;
    *mat4_element(dst, 0, 1) = cy * sz;
    *mat4_element(dst, 0, 2) =-sy;
    *mat4_element(dst, 1, 0) = cz * sx * sy - cx * sz;
    *mat4_element(dst, 1, 1) = cx * cz + sx * sy * sz;
    *mat4_element(dst, 1, 2) = cy * sx;
    *mat4_element(dst, 2, 0) = cx * cz * sy + sx * sz;
    *mat4_element(dst, 2, 1) =-cz * sx + cx * sy * sz;
    *mat4_element(dst, 2, 2) = cx * cy;
    *mat4_element(dst, 0, 3) = 0.0f;
    *mat4_element(dst, 1, 3) = 0.0f;
    *mat4_element(dst, 2, 3) = 0.0f;
    *mat4_element(dst, 3, 0) = 0.0f;
    *mat4_element(dst, 3, 1) = 0.0f;
    *mat4_element(dst, 3, 2) = 0.0f;
    *mat4_element(dst, 3, 3) = 1.0f;
}

void euler_xzy(struct vec3 *angles, mat4 *dst)
{
    float cx, cy, cz, sx, sy, sz;

    sx = sinf(angles->x); cx = cosf(angles->x);
    sy = sinf(angles->y); cy = cosf(angles->y);
    sz = sinf(angles->z); cz = cosf(angles->z);

    *mat4_element(dst, 0, 0) = cy * cz;
    *mat4_element(dst, 0, 1) = sz;
    *mat4_element(dst, 0, 2) =-cz * sy;
    *mat4_element(dst, 1, 0) = sx * sy - cx * cy * sz;
    *mat4_element(dst, 1, 1) = cx * cz;
    *mat4_element(dst, 1, 2) = cy * sx + cx * sy * sz;
    *mat4_element(dst, 2, 0) = cx * sy + cy * sx * sz;
    *mat4_element(dst, 2, 1) =-cz * sx;
    *mat4_element(dst, 2, 2) = cx * cy - sx * sy * sz;
    *mat4_element(dst, 0, 3) = 0.0f;
    *mat4_element(dst, 1, 3) = 0.0f;
    *mat4_element(dst, 2, 3) = 0.0f;
    *mat4_element(dst, 3, 0) = 0.0f;
    *mat4_element(dst, 3, 1) = 0.0f;
    *mat4_element(dst, 3, 2) = 0.0f;
    *mat4_element(dst, 3, 3) = 1.0f;
}

void euler_zyx(struct vec3 *angles, mat4 *dst)
{
    float cx, cy, cz, sx, sy, sz;

    sx = sinf(angles->x); cx = cosf(angles->x);
    sy = sinf(angles->y); cy = cosf(angles->y);
    sz = sinf(angles->z); cz = cosf(angles->z);

    *mat4_element(dst, 0, 0) = cy * cz;
    *mat4_element(dst, 0, 1) = cz * sx * sy + cx * sz;
    *mat4_element(dst, 0, 2) =-cx * cz * sy + sx * sz;
    *mat4_element(dst, 1, 0) =-cy * sz;
    *mat4_element(dst, 1, 1) = cx * cz - sx * sy * sz;
    *mat4_element(dst, 1, 2) = cz * sx + cx * sy * sz;
    *mat4_element(dst, 2, 0) = sy;
    *mat4_element(dst, 2, 1) =-cy * sx;
    *mat4_element(dst, 2, 2) = cx * cy;
    *mat4_element(dst, 0, 3) = 0.0f;
    *mat4_element(dst, 1, 3) = 0.0f;
    *mat4_element(dst, 2, 3) = 0.0f;
    *mat4_element(dst, 3, 0) = 0.0f;
    *mat4_element(dst, 3, 1) = 0.0f;
    *mat4_element(dst, 3, 2) = 0.0f;
    *mat4_element(dst, 3, 3) = 1.0f;
}

void euler_zxy(struct vec3 *angles, mat4 *dst)
{
    float cx, cy, cz, sx, sy, sz;

    sx = sinf(angles->x); cx = cosf(angles->x);
    sy = sinf(angles->y); cy = cosf(angles->y);
    sz = sinf(angles->z); cz = cosf(angles->z);

    *mat4_element(dst, 0, 0) = cy * cz + sx * sy * sz;
    *mat4_element(dst, 0, 1) = cx * sz;
    *mat4_element(dst, 0, 2) =-cz * sy + cy * sx * sz;
    *mat4_element(dst, 1, 0) = cz * sx * sy - cy * sz;
    *mat4_element(dst, 1, 1) = cx * cz;
    *mat4_element(dst, 1, 2) = cy * cz * sx + sy * sz;
    *mat4_element(dst, 2, 0) = cx * sy;
    *mat4_element(dst, 2, 1) =-sx;
    *mat4_element(dst, 2, 2) = cx * cy;
    *mat4_element(dst, 0, 3) = 0.0f;
    *mat4_element(dst, 1, 3) = 0.0f;
    *mat4_element(dst, 2, 3) = 0.0f;
    *mat4_element(dst, 3, 0) = 0.0f;
    *mat4_element(dst, 3, 1) = 0.0f;
    *mat4_element(dst, 3, 2) = 0.0f;
    *mat4_element(dst, 3, 3) = 1.0f;
}

void euler_yzx(struct vec3 *angles, mat4 *dst)
{
    float cx, cy, cz, sx, sy, sz;

    sx = sinf(angles->x); cx = cosf(angles->x);
    sy = sinf(angles->y); cy = cosf(angles->y);
    sz = sinf(angles->z); cz = cosf(angles->z);

    *mat4_element(dst, 0, 0) = cy * cz;
    *mat4_element(dst, 0, 1) = sx * sy + cx * cy * sz;
    *mat4_element(dst, 0, 2) =-cx * sy + cy * sx * sz;
    *mat4_element(dst, 1, 0) =-sz;
    *mat4_element(dst, 1, 1) = cx * cz;
    *mat4_element(dst, 1, 2) = cz * sx;
    *mat4_element(dst, 2, 0) = cz * sy;
    *mat4_element(dst, 2, 1) =-cy * sx + cx * sy * sz;
    *mat4_element(dst, 2, 2) = cx * cy + sx * sy * sz;
    *mat4_element(dst, 0, 3) = 0.0f;
    *mat4_element(dst, 1, 3) = 0.0f;
    *mat4_element(dst, 2, 3) = 0.0f;
    *mat4_element(dst, 3, 0) = 0.0f;
    *mat4_element(dst, 3, 1) = 0.0f;
    *mat4_element(dst, 3, 2) = 0.0f;
    *mat4_element(dst, 3, 3) = 1.0f;
}

void euler_yxz(struct vec3 *angles, mat4 *dst)
{
    float cx, cy, cz, sx, sy, sz;

    sx = sinf(angles->x); cx = cosf(angles->x);
    sy = sinf(angles->y); cy = cosf(angles->y);
    sz = sinf(angles->z); cz = cosf(angles->z);

    *mat4_element(dst, 0, 0) = cy * cz - sx * sy * sz;
    *mat4_element(dst, 0, 1) = cz * sx * sy + cy * sz;
    *mat4_element(dst, 0, 2) =-cx * sy;
    *mat4_element(dst, 1, 0) =-cx * sz;
    *mat4_element(dst, 1, 1) = cx * cz;
    *mat4_element(dst, 1, 2) = sx;
    *mat4_element(dst, 2, 0) = cz * sy + cy * sx * sz;
    *mat4_element(dst, 2, 1) =-cy * cz * sx + sy * sz;
    *mat4_element(dst, 2, 2) = cx * cy;
    *mat4_element(dst, 0, 3) = 0.0f;
    *mat4_element(dst, 1, 0) = 0.0f;
    *mat4_element(dst, 2, 3) = 0.0f;
    *mat4_element(dst, 3, 0) = 0.0f;
    *mat4_element(dst, 3, 1) = 0.0f;
    *mat4_element(dst, 3, 2) = 0.0f;
    *mat4_element(dst, 3, 3) = 1.0f;
}