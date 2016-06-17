#ifndef TEXTURE_FILTER_INCLUDED_52EA5AEA_AF9A_48D3_B808_4FBD5B032C56
#define TEXTURE_FILTER_INCLUDED_52EA5AEA_AF9A_48D3_B808_4FBD5B032C56


#include <stdint.h>


namespace Graphics_api {


/*!
  Texture Options.
  Wrap mode can be clamp or wrap.
  Filtering can be point, bilinear, trilinear or anisotropic.
*/
struct Texture_filtering
{
  uint8_t wrap_mode_s : 2;
  uint8_t wrap_mode_t : 2;
  uint8_t filtering : 4;
};


namespace Filtering_mode {
enum ENUM {

  point = 0,
  bilinear,
  trilinear,
  anisotropic,

}; // enum
} // ns


namespace Wrap_mode {
enum ENUM {

  clamp = 0,
  wrap,

}; // enum
} // ns


} // ns


#endif // inc guard