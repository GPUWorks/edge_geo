#include "ogl_texture_filtering.hpp"


namespace Ogl {


/*
  TODO:
  - What if we are setting a texture that doens't have mips?
  - What if we don't support Anisotropy, or level 4?
*/
void
filtering_apply(const Graphics_api::Texture_filtering settings)
{
  namespace Gfx = Graphics_api;
  
  const auto wrap_s = settings.wrap_mode_s == Gfx::Wrap_mode::clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
  
  const auto wrap_t = settings.wrap_mode_t == Gfx::Wrap_mode::clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT;
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
  
  switch(settings.filtering)
  {
    case(Gfx::Filtering_mode::point):
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      break;
    case(Gfx::Filtering_mode::bilinear):
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      break;
    case(Gfx::Filtering_mode::trilinear):
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      break;
    case(Gfx::Filtering_mode::anisotropic):
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
      break;
  }
}


} // ns