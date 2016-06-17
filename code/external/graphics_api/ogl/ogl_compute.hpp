#ifndef OGL_COMPUTE_INCLUDED_6D9CF190_7C9D_4017_9FE9_C4FAE999506F
#define OGL_COMPUTE_INCLUDED_6D9CF190_7C9D_4017_9FE9_C4FAE999506F


#ifdef GL_HAS_COMPUTE


#include "ogl_common.hpp"
#include "ogl_shader.hpp"


namespace Ogl {


void
compute_shader_create(Shader *out_shader,
                      const char *compute_shader_code);


void
compute_shader_bind(Shader *shader_to_bind);

} // ns


#endif // GL_HAS_COMPUTE


#endif // inc guard