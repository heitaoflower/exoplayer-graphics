//
// Created by showtime on 12/23/2017.
//

#include "ogles_distortion_filter.h"
#include "../../utils/ogles_util.h"
#include "../../geometry/primitive.h"

#include <malloc.h>

#define LINE(s) s "\n"
static const char *vertex_shader_source =
        LINE("uniform float uTextureCoordScale;")
        LINE("attribute vec4 aPosition;")
        LINE("attribute float aVignette;")
        LINE("attribute vec2 aRedTextureCoord;")
        LINE("attribute vec2 aGreenTextureCoord;")
        LINE("attribute vec2 aBlueTextureCoord;")
        LINE("varying highp vec2 vRedTextureCoord;")
        LINE("varying highp vec2 vGreenTextureCoord;")
        LINE("varying highp vec2 vBlueTextureCoord;")
        LINE("varying float vVignette;")
        LINE("void main() {")
        LINE("gl_Position = vec4(aPosition, 0.0, 1.0);")
        LINE("vRedTextureCoord = aRedTextureCoord.xy * uTextureCoordScale;")
        LINE("vGreenTextureCoord = aGreenTextureCoord.xy * uTextureCoordScale;")
        LINE("vBlueTextureCoord = aBlueTextureCoord.xy * uTextureCoordScale;")
        LINE("vVignette = aVignette;")
        LINE("}");

static const char *fragment_shader_source =
        LINE("precision mediump float;")
        LINE("varying vec2 vRedTextureCoord;")
        LINE("varying vec2 vBlueTextureCoord;")
        LINE("varying vec2 vGreenTextureCoord;")
        LINE("varying float vVignette;")
        LINE("uniform sampler2D uTexture;")
        LINE("void main() {")
        LINE("gl_FragColor = vVignette * vec4(texture2D(uTexture, vRedTextureCoord).r, texture2D(uTexture, vGreenTextureCoord).g, texture2D(uTexture, vBlueTextureCoord).b, 1.0);")
        LINE("}");
#undef LINE

ogles_filter_init(distortion)
(struct ogles_distortion_filter *filter, primitive_type primitive_type, bool create_fbo, GLuint texture)
{
    ogles_distortion_filter_safe_release(filter);

    filter->base.vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->base.fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->base.program = createProgram(filter->base.vertex_shader, filter->base.fragment_shader);
    filter->base.primitive = create_primitive(primitive_type);;
    filter->base.fbo = create_fbo ? malloc(sizeof(struct ogles_fbo)) : NULL;
    ogles_distortion_filter_register_handle(filter);
}

ogles_filter_release(distortion)
(struct ogles_distortion_filter *filter)
{

}

ogles_filter_safe_release(distortion)
(struct ogles_distortion_filter *filter)
{

}

ogles_filter_resize(distortion)
(struct ogles_distortion_filter *filter, GLint width, GLint height)
{

}

ogles_filter_pre_draw(distortion)
(struct ogles_distortion_filter *filter, struct ogles_eye *ogles_eye)
{

}

ogles_filter_draw(distortion)
(struct ogles_distortion_filter *filter, GLuint *texture, const float st_mat[], struct ogles_eye *ogles_eye)
{

}

ogles_filter_post_draw(distortion)
(struct ogles_distortion_filter *filter, GLuint *texture, struct ogles_eye *ogles_eye)
{

}

ogles_filter_use_program(distortion)
(struct ogles_distortion_filter *filter)
{

}

ogles_filter_register_handle(distortion)
(struct ogles_distortion_filter *filter)
{

}