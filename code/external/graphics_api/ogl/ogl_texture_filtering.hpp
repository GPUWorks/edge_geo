#ifndef OGL_TEXTURE_FILTERING_INCLUDED_95030160_0168_419D_8767_D1E0AF71D513
#define OGL_TEXTURE_FILTERING_INCLUDED_95030160_0168_419D_8767_D1E0AF71D513


#include "../texture_filtering.hpp"
#include "ogl_common.hpp"
#include <stdint.h>


namespace Ogl {


/*!
  Applies the texture filtering options that it was given.
*/
void
filtering_apply(const Graphics_api::Texture_filtering settings);


} // ns


#endif // inc guard