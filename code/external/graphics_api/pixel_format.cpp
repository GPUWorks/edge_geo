#include "pixel_format.hpp"
#include <utilities/optimizations.hpp>
#include <assert.h>


namespace Graphics_api {


uint32_t
pixel_format_red_bits(const Pixel_format fmt)
{
  switch(fmt)
  {
    case(Pixel_format::rgb8):
    case(Pixel_format::rgba8):
    case(Pixel_format::unknown):
      return 8;
    case(Pixel_format::r32f):
    case(Pixel_format::rgba32f):
      return 32;
    default:
      UNREACHABLE;
      assert(false);
      return 0;
  }
  
  return 0;
}


uint32_t
pixel_format_green_bits(const Pixel_format fmt)
{
  switch(fmt)
  {
    case(Pixel_format::rgb8):
    case(Pixel_format::rgba8):
    case(Pixel_format::unknown):
      return 8;
    case(Pixel_format::rgba32f):
      return 32;
    case(Pixel_format::r32f):
      return 0;
    default:
      UNREACHABLE;
      assert(false);
      return 0;
  }
  UNREACHABLE;
  return 0;
}


uint32_t
pixel_format_blue_bits(const Pixel_format fmt)
{
  switch(fmt)
  {
    case(Pixel_format::rgb8):
    case(Pixel_format::rgba8):
    case(Pixel_format::unknown):
      return 8;
    case(Pixel_format::rgba32f):
      return 32;
    case(Pixel_format::r32f):
      return 0;
    default:
      UNREACHABLE;
      assert(false);
      return 0;
  }
  UNREACHABLE;
  return 0;
}

uint32_t
pixel_format_alpha_bits(const Pixel_format fmt)
{
  switch(fmt)
  {
    case(Pixel_format::rgb8):
    case(Pixel_format::r32f):
      return 0;
    case(Pixel_format::rgba8):
    case(Pixel_format::unknown):
      return 8;
    case(Pixel_format::rgba32f):
      return 32;
    default:
      UNREACHABLE;
      assert(false);    
      return 0;
  }
  UNREACHABLE;
  return 0;
}


} // ns