//
// Created by showtime on 9/5/2017.
//
#include "glUtil.h"

void setupSampler(GLenum target, GLfloat mag, GLfloat min)
{
    glTexParameterf(target, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameterf(target, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

