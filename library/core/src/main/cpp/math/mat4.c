//
// Created by showtime on 9/12/2017.
//

#include "mat4.h"
#include "../utils/log_util.h"

#include <string.h>
#include <math.h>
#include <assert.h>

inline static float length(float x, float y, float z)
{
    return sqrtf(x * x + y * y + z * z);
}

float* mat4_element(mat4 *mat, int row, int col)
{
    return (float*)mat + (row + (col << 2));
}

void mat4_identity(mat4 *mat)
{
    mat4_zero(mat);

    for (int i = 0; i < 4; i++)
    {
        *mat4_element(mat, i, i) = 1.0f;
    }
}

void mat4_zero(mat4 *mat)
{
    memset(mat, 0, sizeof(*mat));
}

void mat4_multiply(mat4 *dst, mat4 *src1, mat4 *src2)
{
    mat4 mat;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            *mat4_element(&mat, i, j) =
                    *mat4_element(src1, i, 0) * *mat4_element(src2, 0, j) +
                    *mat4_element(src1, i, 1) * *mat4_element(src2, 1, j) +
                    *mat4_element(src1, i, 2) * *mat4_element(src2, 2, j) +
                    *mat4_element(src1, i, 3) * *mat4_element(src2, 3, j);
        }

    }

    memcpy(dst, &mat, sizeof(mat4));
}

/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glFrustum.xml
*
* perspective matrix:
*
* /   2 * nearVal                                \
* |  ------------       0            A      0    |
* |  right - left                                |
* |                                              |
* |                 2 * nearVal                  |
* |       0        ------------      B      0    |
* |                top - bottom                  |
* |                                              |
* |       0             0            C      D    |
* |                                              |
* |       0             0           -1      0    |
* \                                              /
*
*     right + left
* A = ------------
*     right - left
*
*     top + bottom
* B = ------------
*     top - bottom
*
*       farVal + nearVal
* C = - ----------------
*       farVal - nearVal
*
*       2 * farVal * nearVal
* D = - --------------------
*         farVal - nearVal
*
*/
void mat4_frustum(mat4 *mat, float left, float right, float bottom, float top, float nearVal, float farVal)
{
    float A = (right + left) / (right - left);
    float B = (top + bottom) / (top - bottom);
    float C = - (farVal + nearVal) / (farVal - nearVal);
    float D = - (2.0f * farVal * nearVal) / (farVal - nearVal);

    mat4_zero(mat);

    *mat4_element(mat, 0, 0) = (2.0f * nearVal) / (right - left);
    *mat4_element(mat, 0, 2) = A;
    *mat4_element(mat, 1, 1) = (2.0f * nearVal) / (top - bottom);
    *mat4_element(mat, 1, 2) = B;
    *mat4_element(mat, 2, 2) = C;
    *mat4_element(mat, 2, 3) = D;
    *mat4_element(mat, 3, 2) = -1.0f;
}

void mat4_ortho(mat4 *mat, float left, float right, float bottom, float top, float nearVal, float farVal)
{
    float r_width  = 1.0f / (right - left);
    float r_height = 1.0f / (top - bottom);
    float r_depth  = 1.0f / (farVal - nearVal);
    float x =  2.0f * (r_width);
    float y =  2.0f * (r_height);
    float z = -2.0f * (r_depth);
    float tx = -(right + left) * r_width;
    float ty = -(top + bottom) * r_height;
    float tz = -(farVal + nearVal) * r_depth;

    mat4_zero(mat);

    *mat4_element(mat, 0, 0) = x;
    *mat4_element(mat, 1, 1) = y;
    *mat4_element(mat, 2, 2) = z;
    *mat4_element(mat, 3, 0) = tx;
    *mat4_element(mat, 3, 1) = ty;
    *mat4_element(mat, 3, 2) = tz;
    *mat4_element(mat, 3, 3) = 1.0f;
}

void mat4_ortho_default(mat4 *mat, float aspect)
{
    if (aspect >= 1.0f)
    {
        mat4_ortho(mat,
                   -1.0f * aspect,
                    1.0f * aspect,
                   -1.0f,
                    1.0f,
                   -1000.0f,
                    1000.0f);
    }
    else
    {
        mat4_ortho(mat,
                   -1.0f,
                    1.0f,
                   -1.0f * aspect,
                    1.0f * aspect,
                   -1000.0f,
                    1000.0f);
    }
}
/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml
*
* f = cotangent(fovy / 2)
*
* perspective matrix:
*
* /    f                                                  \
* |  ------       0          0                 0          |
* |  aspect                                               |
* |                                                       |
* |    0          f          0                 0          |
* |                                                       |
* |                     zFar + zNear    2 * zFar * zNear  |
* |    0          0    --------------  ------------------ |
* |                     zNear - zFar      zNear - zFar    |
* |                                                       |
* |    0          0         -1                 0          |
* \                                                       /
*
*/
void mat4_perspective(mat4 *mat, float fovy, float aspect, float zNear, float zFar)
{
    float f = (1.0f / tanf(fovy / 2.0f));
    mat4_zero(mat);

    assert(aspect != 0.0 && zNear != zFar);

    *mat4_element(mat, 0, 0) = f / aspect;
    *mat4_element(mat, 1, 1) = f;
    *mat4_element(mat, 2, 2) = (zFar + zNear) / (zNear - zFar);
    *mat4_element(mat, 3, 2) = -1.0f;
    *mat4_element(mat, 2, 3) = (2.0f * zFar * zNear) / (zNear - zFar);
}

void mat4_perspective_default(mat4 *mat, float aspect)
{
    mat4_perspective(mat, deg2rad(60), aspect, 0.03f, 1000);
}

void mat4_lookat(mat4 *mat, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
    float fx = centerX - eyeX;
    float fy = centerY - eyeY;
    float fz = centerZ - eyeZ;

    // Normalize f
    float rlf = 1.0f / length(fx, fy, fz);
    fx *= rlf;
    fy *= rlf;
    fz *= rlf;

    // compute s = f x up (x means "cross product")
    float sx = fy * upZ - fz * upY;
    float sy = fz * upX - fx * upZ;
    float sz = fx * upY - fy * upX;

    // and normalize s
    float rls = 1.0f / length(sx, sy, sz);
    sx *= rls;
    sy *= rls;
    sz *= rls;

    // compute u = s x f
    float ux = sy * fz - sz * fy;
    float uy = sz * fx - sx * fz;
    float uz = sx * fy - sy * fx;

    *mat4_element(mat, 0, 0) = sx;
    *mat4_element(mat, 0, 1) = ux;
    *mat4_element(mat, 0, 2) = -fx;
    *mat4_element(mat, 0, 3) = 0.0f;

    *mat4_element(mat, 1, 0) = sy;
    *mat4_element(mat, 1, 1) = uy;
    *mat4_element(mat, 1, 2) = -fy;
    *mat4_element(mat, 1, 3) = 0.0f;

    *mat4_element(mat, 2, 0) = sz;
    *mat4_element(mat, 2, 1) = uz;
    *mat4_element(mat, 2, 2) = -fz;
    *mat4_element(mat, 2, 3) = 0.0f;

    *mat4_element(mat, 3, 0) = 0.0f;
    *mat4_element(mat, 3, 1) = 0.0f;
    *mat4_element(mat, 3, 2) = 0.0f;
    *mat4_element(mat, 3, 3) = 1.0f;

    mat4_translate(mat, -eyeX, -eyeY, -eyeZ);
}


/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glTranslate.xml
*
* /              \
* |  1  0  0  x  |
* |              |
* |  0  1  0  y  |
* |              |
* |  0  0  1  z  |
* |              |
* |  0  0  0  1  |
* \              /
*
*/
void mat4_set_translate(mat4 *mat, float x, float y, float z)
{
    mat4_zero(mat);

    *mat4_element(mat, 0, 0) = 1.0;
    *mat4_element(mat, 1, 1) = 1.0;
    *mat4_element(mat, 2, 2) = 1.0;
    *mat4_element(mat, 3, 3) = 1.0;
    *mat4_element(mat, 0, 3) = x;
    *mat4_element(mat, 1, 3) = y;
    *mat4_element(mat, 2, 3) = z;
}

void mat4_translate(mat4 *mat, float x, float y, float z)
{
    for (int i = 0 ; i < 4 ; i++)
    {
        *mat4_element(mat, i, 3) += *mat4_element(mat, i, 0) * x + *mat4_element(mat, i, 1) * y + *mat4_element(mat, i, 2) * z;
    }
}

/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml
*
* /                                                          \
* | x^2*(1-c) + c     x*y*(1-c) - z*s   x*z*(1-c) + y*s   0  |
* |                                                          |
* | y*x*(1-c) + z*s   y^2*(1-c) + c     y*z*(1-c) - x*s   0  |
* |                                                          |
* | x*z*(1-c) - y*s   y*z*(1-c) + x*s   z^2*(1-c) + c     0  |
* |                                                          |
* |       0                  0                 0          1  |
* \                                                          /
*
* c = cos(angle), s = sin(angle)
*
*/
void mat4_rotate(mat4 *mat, float angle, float x, float y, float z)
{
    mat4 tmp;
    mat4_set_rotate(&tmp, angle, x, y, z);
    mat4_multiply(mat, mat, &tmp);
}

void mat4_set_rotate(mat4 *mat, float angle, float x, float y, float z)
{
    float c = (float)cos(angle);
    float omc = 1.0f - c;
    float s = (float)sin(angle);

    mat4_zero(mat);

    *mat4_element(mat, 0, 0) = (x * x * omc) + c;
    *mat4_element(mat, 0, 1) = (x * y * omc) - z * s;
    *mat4_element(mat, 0, 2) = (x * z * omc) + y * s;
    *mat4_element(mat, 1, 0) = (y * x * omc) + z * s;
    *mat4_element(mat, 1, 1) = (y * y * omc) + c;
    *mat4_element(mat, 1, 2) = (y * z * omc) - x * s;
    *mat4_element(mat, 2, 0) = (z * x * omc) - y * s;
    *mat4_element(mat, 2, 1) = (z * y * omc) + x * s;
    *mat4_element(mat, 2, 2) = (z * z * omc) + c;
    *mat4_element(mat, 3, 3) = 1.0;
}

void mat4_scale(mat4 *mat, float x, float y, float z)
{
    *mat4_element(mat, 0, 0) *= x;
    *mat4_element(mat, 0, 1) *= x;
    *mat4_element(mat, 0, 2) *= x;
    *mat4_element(mat, 0, 3) *= x;

    *mat4_element(mat, 1, 0) *= y;
    *mat4_element(mat, 1, 1) *= y;
    *mat4_element(mat, 1, 2) *= y;
    *mat4_element(mat, 1, 3) *= y;

    *mat4_element(mat, 2, 0) *= z;
    *mat4_element(mat, 2, 1) *= z;
    *mat4_element(mat, 2, 2) *= z;
    *mat4_element(mat, 2, 3) *= z;
}


/* https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glScale.xml
*
* /              \
* |  x  0  0  0  |
* |              |
* |  0  y  0  0  |
* |              |
* |  0  0  z  0  |
* |              |
* |  0  0  0  1  |
* \              /
*
*/
void mat4_set_scale(mat4 *mat, float x, float y, float z)
{
    mat4_zero(mat);

    *mat4_element(mat, 0, 0) = x;
    *mat4_element(mat, 1, 1) = y;
    *mat4_element(mat, 2, 2) = z;
    *mat4_element(mat, 3, 3) = 1;
}

void mat4_print(mat4 *mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            LOGI("row = %d , col = %d, value = %f ",j, i, *mat4_element(mat, j, i));
        }
    }
}