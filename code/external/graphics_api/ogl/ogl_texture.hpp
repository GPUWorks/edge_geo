#ifndef OGL_TEXTURE_INCLUDED_530B56CF_2269_430E_ACC6_04D56756ACC4
#define OGL_TEXTURE_INCLUDED_530B56CF_2269_430E_ACC6_04D56756ACC4


#include "ogl_common.hpp"
#include <stdint.h>
#include <assert.h>


namespace Ogl {


/*!
  Texture Object.
  TODO: Pack this down. ideally under 128bits or less.
*/
struct Texture
{
  GLuint          texture_id  = 0;
  GLenum          format      = GL_RGBA;
  GLenum          dimention   = GL_TEXTURE_2D;
  uint32_t        width       = 0;
  uint32_t        height      = 0;
  uint32_t        depth       = 0;
}; // struct


/*!
  Creates a texture from the given data.
  \param out_texture The texture to generate.
  \param width The width of the texture data.
  \param height The height of the texture data.
  \param Pixel_format The desired format of the pixels.
  \param data Pointer to the raw data in memory.
  \param log Optional logging stream.
*/
void
texture_create_2d(Texture *out_texture,
                  const uint32_t width,
                  const uint32_t height,
                  const GLenum format,
                  const void *data,
                  const bool mips = true,
                  std::ostream *log = nullptr);



/*!
  Update the data in a texture.
  \param update_texture The target to update.
  \param offset_x Starting point of the update.
  \param offset_y Starting point of the update.
  \param width Width of the update.
  \param height Height of the update.
  \param data Pointer to the raw data in memory.
  \param log Optional logging stream.
*/
void
texture_update_texture_2d(Texture *update_texture,
                          const uint32_t offset_x,
                          const uint32_t offset_y,
                          const uint32_t width,
                          const uint32_t height,
                          const void *data,
                          std::ostream *log = nullptr);

/*!
  Simplisitc sugar method that just checks it has a
  non zero texture id.
  \param check_is_valid Texture to check.
*/
inline bool
texture_is_valid(const Texture *check_is_valid)
{
  return check_is_valid->texture_id > 0;
}


} // ns


#endif // inc guard