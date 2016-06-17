#include "shader_utils.hpp"
#include <utilities/string_helpers.hpp>
#include <fstream>
#include <streambuf>
#include <string>


namespace Graphics_api {
namespace Util {


Shader_code
shader_code_from_tagged_file(const char *filename)
{
  const std::string code(std::istreambuf_iterator<char>(std::ifstream(filename).rdbuf()), std::istreambuf_iterator<char>());
  
  const std::string get_filepath = util::get_dir_from_filepath(filename);
  const std::string pre_processed = util::hash_include_string(code, {get_filepath});
  
  return shader_code_from_tagged_string(pre_processed.c_str());
}


Shader_code
shader_code_from_tagged_string(const char *code)
{
  auto parse_file = [](const std::string &combined_shader, const std::string &tag_name) -> std::string
  {
    const std::string open_tag  = "[" + tag_name + "]";
    const std::string close_tag = "[/" + tag_name + "]";

    const std::size_t shader_start = combined_shader.find(open_tag);
    const std::size_t shader_end = combined_shader.find(close_tag);

    if((shader_start != std::string::npos) && (shader_end != std::string::npos))
    {
      const std::size_t start = shader_start + open_tag.size();
      const std::size_t size = shader_end - start;

      const std::string shader = combined_shader.substr(start, size);

      return shader;
    }

    return "";
  };

  const auto vs = parse_file(code, "VERTEX");
  const auto gs = parse_file(code, "GEOMETRY");
  const auto ps = parse_file(code, "PIXEL");
  const auto cs = parse_file(code, "COMPUTE");

  return Shader_code{vs, gs, ps, cs};
}


} // ns
} // ns