#ifndef CLEAR_INCLUDED_DC6F1449_F32A_481C_A191_DBC0C76B3E7B
#define CLEAR_INCLUDED_DC6F1449_F32A_481C_A191_DBC0C76B3E7B


#include <stdint.h>


namespace Graphics_api {


namespace Clear_flag {
enum ENUM : uint32_t {
  
  color    = 1 << 0,
  depth    = 1 << 1,
  
};
} // ns


/*!
  Or flags you wish to clear together.
*/
void
clear(const uint32_t clear_flags);


/*!
  Set the clear color.
*/
void
clear_color_set(const float r, const float g, const float b);


} // ns


#endif // inc guard