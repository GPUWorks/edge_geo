#ifndef BLEND_INCLUDED_E19A49F1_E0DC_48F7_B86E_3C0DFD53893A
#define BLEND_INCLUDED_E19A49F1_E0DC_48F7_B86E_3C0DFD53893A


#include "ogl_common.hpp"


namespace Ogl {


/*!
  Convenice method that enables blending before you use it.
*/
inline void
blend(const GLenum src, const GLenum dest)
{
  glEnable(GL_BLEND);
  glBlendFunc(src, dest);
}


/*!
  Convenice method that sets blending to the default.
*/
inline void
blend_default()
{
  Ogl::blend(GL_ONE, GL_ZERO);
}


} // ns


#endif // inc guard