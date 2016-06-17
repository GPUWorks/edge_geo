#include "ogl_shader_uniform.hpp"
#include "ogl_shader.hpp"
#include <utilities/optimizations.hpp>
#include <assert.h>


namespace Ogl {


void
shader_uniforms_retrive(Shader_uniforms *out_uniforms, const Shader *shader)
{
  if(!shader)
  {
    assert(false);
    return;
  }

  glUseProgram(shader->program_id);

  // Get uniforms.
  GLint uniform_count, uniform_length;
  glGetProgramiv(shader->program_id, GL_ACTIVE_UNIFORMS, &uniform_count);
  glGetProgramiv(shader->program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &uniform_length);

  std::vector<std::string>  sampler_names;
  std::vector<Uniform>      samplers;
  samplers.reserve(uniform_count);
  sampler_names.reserve(uniform_count);
  
  std::vector<std::string>  constant_names;
  std::vector<Uniform>      constants;
  constants.reserve(uniform_count);
  constant_names.reserve(uniform_count);

  for(GLint i = 0; i < uniform_count; ++i)
  {
    GLenum gl_type = 0;
    GLint length   = 0;
    GLint size     = 0;

    std::vector<GLchar> uni_name;
    uni_name.reserve(uniform_length);

    glGetActiveUniform(shader->program_id, i, uniform_length, &length, &size, &gl_type, uni_name.data());
    const std::string uniform_name(uni_name.data());

    // Is sampler?
    if((gl_type >= GL_SAMPLER_1D) && (gl_type <= GL_SAMPLER_2D_RECT_SHADOW))
    {
      const GLint location = glGetUniformLocation(shader->program_id, uniform_name.c_str());

      glUniform1i(location, static_cast<GLint>(samplers.size()));

      sampler_names.emplace_back(uniform_name);
      samplers.emplace_back(Uniform{static_cast<GLint>(samplers.size()), gl_type, 0});
    }
    // Then uniform
    else
    {
      const std::string prefix = "gl_";

      if(uniform_name.compare(0, prefix.length(), prefix) != 0)
      {
        const GLint index = glGetUniformLocation(shader->program_id, uniform_name.c_str());

        constant_names.emplace_back(uniform_name);
        constants.emplace_back(Uniform{index, gl_type, static_cast<int32_t>(size)});
      }
    }
  }
  
  glUseProgram(0);

  sampler_names.shrink_to_fit();
  constant_names.shrink_to_fit();
  samplers.shrink_to_fit();
  constants.shrink_to_fit();
  
  out_uniforms->sampler_names = std::move(sampler_names);
  out_uniforms->samplers = std::move(samplers);
  out_uniforms->uniform_names = std::move(constant_names);
  out_uniforms->uniforms = std::move(constants);
}


bool
shader_uniforms_get_uniform_index(Uniform *out_index, const Shader_uniforms *unis, const std::string &name)
{
  assert(out_index && unis);
  
  for(std::uint32_t i = 0; i < unis->uniform_names.size(); ++i)
  {
    if(unis->uniform_names[i] == name)
    {
      (*out_index) = unis->uniforms[i];
      return true;
    }
  }
  
  for(std::uint32_t i = 0; i < unis->sampler_names.size(); ++i)
  {
    if(unis->sampler_names[i] == name)
    {
      (*out_index) = unis->samplers[i];
      return true;
    }
  }
  
  // Make it invalid
  out_index->index = -1;
  out_index->number_of_elements = 0;
  out_index->type = 0;
  
  return false;
}


void
shader_uniforms_apply(const Uniform uniform_to_apply, void *data)
{
  switch(uniform_to_apply.type)
  {
    case(GL_FLOAT):       glUniform1fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLfloat*)data);  break;
    case(GL_FLOAT_VEC2):  glUniform2fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLfloat*)data);  break;
    case(GL_FLOAT_VEC3):  glUniform3fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLfloat*)data);  break;
    case(GL_FLOAT_VEC4):  glUniform4fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLfloat*)data);  break;
    case(GL_INT):         glUniform1iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_INT_VEC2):    glUniform2iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_INT_VEC3):    glUniform3iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_INT_VEC4):    glUniform4iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_BOOL):        glUniform1iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_BOOL_VEC2):   glUniform2iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_BOOL_VEC3):   glUniform3iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_BOOL_VEC4):   glUniform4iv(uniform_to_apply.index, uniform_to_apply.number_of_elements, (GLint*)data);    break;
    case(GL_FLOAT_MAT2):  glUniformMatrix2fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, GL_FALSE, (GLfloat*)data); break;
    case(GL_FLOAT_MAT3):  glUniformMatrix3fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, GL_FALSE, (GLfloat*)data); break;
    case(GL_FLOAT_MAT4):  glUniformMatrix4fv(uniform_to_apply.index, uniform_to_apply.number_of_elements, GL_FALSE, (GLfloat*)data); break;
    case(GL_SAMPLER_1D):
    case(GL_SAMPLER_1D_ARRAY):
    case(GL_SAMPLER_1D_ARRAY_SHADOW):
    case(GL_SAMPLER_1D_SHADOW):
    case(GL_SAMPLER_2D):
    case(GL_SAMPLER_2D_ARRAY):
    case(GL_SAMPLER_2D_ARRAY_SHADOW):
    case(GL_SAMPLER_2D_MULTISAMPLE):
    case(GL_SAMPLER_2D_MULTISAMPLE_ARRAY):
    case(GL_SAMPLER_2D_RECT):
    case(GL_SAMPLER_2D_RECT_SHADOW):
    case(GL_SAMPLER_2D_SHADOW):
    case(GL_SAMPLER_3D):
    {
      // There are other samplers but do we need them?
      GLint tex_id = *static_cast<GLint*>(data);
      
      glActiveTexture(GL_TEXTURE0 + uniform_to_apply.index);
      glBindTexture(GL_TEXTURE_2D, tex_id);
      break;
    }

    default:
      UNREACHABLE;
      assert(false); // Why did you get here?
  };  
}


} // ns