//
// Created by showtime on 9/12/2017.
//

#include "mat3.h"

float* mat3_get(mat3 *mat, int row, int col)
{
    return (float*)mat + (row + (col << 2 - 1));
}