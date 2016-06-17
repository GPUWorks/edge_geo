#ifndef PIXEL_FORMAT_INCLUDED_A26C33CD_4B44_4B8C_B71D_4F87D12AE653
#define PIXEL_FORMAT_INCLUDED_A26C33CD_4B44_4B8C_B71D_4F87D12AE653


#include <stdint.h>


namespace Graphics_api {


enum class Pixel_format : uint8_t
{
  rgb8,
  rgba8,
  rgba32f,
  r32f,
  
  unknown,
};


/*!
  Returns the number of red bits in a format.
*/
uint32_t
pixel_format_red_bits(const Pixel_format fmt);


/*!
  Returns the number of green bits in a format.
*/
uint32_t
pixel_format_green_bits(const Pixel_format fmt);


/*!
  Returns the number of blue bits in a format.
*/
uint32_t
pixel_format_blue_bits(const Pixel_format fmt);


/*!
  Returns the number of alpha bits in a format.
*/
uint32_t
pixel_format_alpha_bits(const Pixel_format fmt);


} // ns


#endif // inc guard