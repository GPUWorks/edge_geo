#ifndef OGL_SHADER_INCLUDED_4A57DD2B_3994_4F0A_9AC8_B9374A867208
#define OGL_SHADER_INCLUDED_4A57DD2B_3994_4F0A_9AC8_B9374A867208


#include "ogl_common.hpp"


namespace Ogl {


/*!
  A GL shader program.
*/
struct Shader
{
  GLuint program_id        = 0;
  GLuint vert_shader_id    = 0;
  GLuint geo_shader_id     = 0;
  GLuint frag_shader_id    = 0;
  GLuint compute_shader_id = 0;
};


/*!
  Attempts to create a shader for rendering.
  \param out_shader The shader output.
  \param vert_shader_code The vertex shader code.
  \param geo_shader_code The geometry shader code, this is optional.
  \param frag_shader_code The fragment shader code.
  \param log Optional logging stream.
*/
void
shader_create(Shader *out_shader,
              const char *vert_shader_code,
              const char *geo_shader_code,
              const char *frag_shader_code);

/*!
  Attempts to create a shader for rendering.
  \param shader_to_destroy The shader that will be destroyed.
  \param log Optional logging stream.
*/
void
shader_destroy(Shader *shader_to_destroy,
               std::ostream *log = nullptr);


/*!
  Bind a shader, passing null will unbind current shader.
  \param shader_to_bind is the shader to bind o_O.
*/
void
shader_bind(const Shader *shader_to_bind);


/*!
  Checks if a shader is valid or not.
  This simply checks if program_id has a value.
  \param shader_to_check This is the shader to test.
*/
inline bool
shader_is_valid(const Shader *shader_to_check)
{
  return shader_to_check->program_id != 0;
}


namespace Detail {


/*!
  Compiles an individual shader program.
  Does not do any linking etc.
  \param shader_type Should be GL_VERTEX_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER, or GL_COMPUTE_SHADER
  \param shader_code Is the code to compile.
*/
GLuint
compile_shader(const GLenum shader_type,
               const char *shader_code);


} // ns


} // ns


#endif // inc guard