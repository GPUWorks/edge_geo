#include "clear.hpp"
#include "ogl/ogl_common.hpp"


namespace Graphics_api {


void
clear(const uint32_t flags)
{
  Ogl::clear(flags & Clear_flag::color, flags & Clear_flag::depth);
}


void
clear_color_set(const float r, const float g, const float b)
{
  Ogl::clear_color(r, g, b);
}


} // ns