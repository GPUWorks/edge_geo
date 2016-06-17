#ifndef OGL_FRAME_BUFFER_INCLUDED_643DDCC0_3A1B_4204_A2D2_8B3210733CEA
#define OGL_FRAME_BUFFER_INCLUDED_643DDCC0_3A1B_4204_A2D2_8B3210733CEA


#include "ogl_common.hpp"
#include "ogl_texture.hpp"
#include <stdint.h>
#include <assert.h>


#define GFX_API_GL_MAX_NUMBER_OF_OUTPUTS 4


namespace Ogl {


struct Frame_buffer
{
  GLuint          fbo_id;
  Texture         color_buffer[GFX_API_GL_MAX_NUMBER_OF_OUTPUTS];
  Texture         depth_buffer;
  Texture         stencil_buffer;
}; // struct


/*
  Creates a framebuffer.
*/
void
frame_buffer_create(Frame_buffer *out_frame_buffer,
                   Texture output_textures[],
                   const uint32_t number_of_outputs,
                   Texture *depth_buffer,
                   Texture *stencil_buffer);


/*
  Bind a framebuffer.
*/
void
frame_buffer_bind(Frame_buffer *fbo);


/*
  Sugar unbind function.
*/
void
frame_buffer_unbind();


/*
  Checks if the framebuffer is valid
*/
bool
frame_buffer_is_valid(Frame_buffer *fbo);

} // ns


#endif // inc guard