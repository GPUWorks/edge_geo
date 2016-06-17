#ifndef SHADER_UTILS_INCLUDED_F663A519_BB89_4AFA_9036_038526F71B5F
#define SHADER_UTILS_INCLUDED_F663A519_BB89_4AFA_9036_038526F71B5F


#include <string>


namespace Graphics_api {
namespace Util {


struct Shader_code
{
  std::string vs_code;
  std::string gs_code;
  std::string ps_code;
  std::string cs_code;
};


Shader_code
shader_code_from_tagged_file(const char *filename);


Shader_code
shader_code_from_tagged_string(const char *code);


} // ns
} // ns


#endif // inc guard