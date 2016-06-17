#ifndef SHADER_UNIFORM_INCLUDED_824F6A90_7EB3_46BB_AEF3_4A9B3F01AD0A
#define SHADER_UNIFORM_INCLUDED_824F6A90_7EB3_46BB_AEF3_4A9B3F01AD0A


#include "ogl_fwd.hpp"
#include "ogl_common.hpp"
#include <stdint.h>
#include <string>
#include <vector>


namespace Ogl {


/*!
  Structure for a GL Uniform.
*/
struct Uniform
{
  GLint       index;
  GLenum      type;
  GLint       number_of_elements;
};


/*!
  Structure for uniforms that apply to a shader.
*/
struct Shader_uniforms
{
  std::vector<std::string>  uniform_names;
  std::vector<Uniform>      uniforms;
  
  std::vector<std::string>  sampler_names;
  std::vector<Uniform>      samplers;
};


/*!
  Gets the uniform and sampler info from a shader.
  \param out_uniforms the result.
  \param shader a valid shader.
*/
void
shader_uniforms_retrive(Shader_uniforms *out_uniforms, const Shader *shader);


/*!
  Searches for the index for the requested uniform.
  \param out_uniform, the uniforms reesult.
  \param unis pointer to shader_uniforms.
  \param name name of the uniform.
  \return true or false depending of if it was found.
*/
bool
shader_uniforms_get_uniform_index(Uniform *out_uniform, const Shader_uniforms *unis, const std::string &name);


/*!
 Applys a uniform to the currently bound shader.
 \param uniform_to_apply The uniform to apply to the current shader.
 \param data The data to be uploaded to the uniform.
*/
void
shader_uniforms_apply(const Uniform uniform_to_apply, void *data);


} // ns


#endif // inc guard