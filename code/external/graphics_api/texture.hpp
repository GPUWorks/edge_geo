#ifndef TEXTURE_INCLUDED_6B294778_F9E5_4AB0_8266_239C14EF972D
#define TEXTURE_INCLUDED_6B294778_F9E5_4AB0_8266_239C14EF972D


#include <stdint.h>
#include "gfx_common.hpp"
#include "pixel_format.hpp"
#include "dimention.hpp"
#include "ogl/ogl_texture.hpp"


namespace Graphics_api {


struct Texture : public API_TYPE::Texture
{
  Pixel_format  requested_format;
  Dimention     requested_dimention;
};


Texture
texture_load_from_data(const Dimention dimention,
                       const Pixel_format format,
                       const uint32_t width,
                       const uint32_t height,
                       const uint32_t depth,
                       const void* data);


Texture
texture_load_from_file(const Dimention dimention,
                       const Pixel_format format,
                       const char* file);


bool
texture_is_valid(const Texture *texture);


uint32_t
texture_get_width(Texture *texture);


uint32_t
texture_get_height(Texture *texture);


uint32_t
texture_get_depth(Texture *texture);


Pixel_format
texture_get_pixel_format(Texture *texture);


} // ns


#endif // inc guard