#include "ogl_frame_buffer.hpp"
#include <algorithm>


namespace Ogl {


void
frame_buffer_create(Frame_buffer *out_frame_buffer,
                   Texture output_textures[],
                   const uint32_t number_of_outputs,
                   Texture *depth_buffer,
                   Texture *stencil_buffer)
{
  // Generate the fbo
  memset(out_frame_buffer, 0, sizeof(Frame_buffer));

  glGenFramebuffers(1, &out_frame_buffer->fbo_id);
  glBindFramebuffer(GL_FRAMEBUFFER, (GLuint)out_frame_buffer->fbo_id);
  
  // Attach the color buffers.
  const uint32_t outputs = std::min<uint32_t>(GFX_API_GL_MAX_NUMBER_OF_OUTPUTS, number_of_outputs);
  
  for(uint32_t out = 0; out < outputs; ++out)
  {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + out, GL_TEXTURE_2D, output_textures[out].texture_id, 0);
    out_frame_buffer->color_buffer[out] = output_textures[out];
  }
  
  // Attach depth if it exists.
  if(depth_buffer)
  {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_buffer->texture_id, 0);
    out_frame_buffer->depth_buffer = *depth_buffer;
  }
  
  // Attach stencil if it exists.
  if(stencil_buffer)
  {
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, stencil_buffer->texture_id, 0);
    out_frame_buffer->stencil_buffer = *stencil_buffer;
  }
  
  // Check the framebuffer.
  const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    assert(false); // this shoudl be logging of some sort.
  }

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



void
frame_buffer_bind(Frame_buffer *fbo)
{
  glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo_id);
}


void
frame_buffer_unbind()
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


bool
frame_buffer_is_valid(Frame_buffer *fbo)
{
  glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo_id);
  const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  return status == GL_FRAMEBUFFER_COMPLETE;
}



} // ns