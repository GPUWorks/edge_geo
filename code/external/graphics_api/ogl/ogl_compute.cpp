
#ifdef GL_HAS_COMPUTE

#include "ogl_compute.hpp"
#include <assert.h>


namespace Ogl {


void
compute_shader_create(Shader *out_shader,
                      const char *compute_shader_code)
{
  assert(out_shader);
  
  const auto compute_shader_id = Detail::compile_shader(GL_COMPUTE_SHADER, compute_shader_code);
  LOG_GL_ERROR("Creating compute shader");
}


void
compute_shader_bind(Shader *shader_to_bind)
{
  
}


} // ns


#endif // GL_HAS_COMPUTE