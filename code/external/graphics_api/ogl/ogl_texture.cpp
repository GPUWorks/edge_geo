#include "ogl_texture.hpp"
#include "ogl_pixel_format.hpp"


namespace Ogl {


void
texture_create_2d(Texture *out_texture,
                  const uint32_t width,
                  const uint32_t height,
                  const GLenum format,
                  const void *data,
                  const bool mips,
                  std::ostream *log)
{
  // Param check
  if(!out_texture || !width || !height)
  {
    assert(false); // Param fail
    
    if(log)
    {
      if(!width || !height)
      {
        (*log) << "Incorrect paramaters given to 'Ogl::texture_create_2d': ";
        (*log) << "'width' or 'height' are not valid.\n";
      }
      
      if(!out_texture)
      {
        (*log) << "Incorrect paramaters given to 'Ogl::texture_create_2d': ";
        (*log) << "'out_texture' may not be null.\n";
      }
      
      if(!data)
      {
        (*log) << "Incorrect paramaters given to 'Ogl::texture_create_2d': ";
        (*log) << "'data' may not be null.\n";
      }
    }
  
    return;
  }
  
  // Set some arguments
  out_texture->format    = format;
  out_texture->width     = width;
  out_texture->height    = height;
  out_texture->dimention = GL_TEXTURE_2D;
  
  const auto pixel_format      = pixel_format_get_format(format);
  const auto pixel_format_type = pixel_format_get_type(format);
  
  // Open GL
  glGenTextures(1, &out_texture->texture_id);
    Ogl::error_check("2", &std::cout);

  glBindTexture(GL_TEXTURE_2D, out_texture->texture_id);
    Ogl::error_check("3", &std::cout);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               format,
               width,
               height,
               0,
               pixel_format,
               pixel_format_type,
               data);
    Ogl::error_check("4", &std::cout);
  
    if(mips)
    {

  glGenerateMipmap(GL_TEXTURE_2D);
  }
    Ogl::error_check("5", &std::cout);

}



void
texture_update_texture_2d(Texture *update_texture,
                          const uint32_t offset_x,
                          const uint32_t offset_y,
                          const uint32_t width,
                          const uint32_t height,
                          const void *data,
                          std::ostream *log)
{
  // Param check
  if(!update_texture || !data || (width + offset_x) > update_texture->width || (height + offset_y) > update_texture->height)
  {
    assert(false); // Param fail
    
    if(log)
    {
      if(!update_texture)
      {
        (*log) << "Incorrect paramaters given to Ogl::texture_update_texture_2d: ";
        (*log) << "'update_texture' may not be null.\n";
      }
      
      if(!data)
      {
        (*log) << "Incorrect paramaters given to Ogl::texture_update_texture_2d: ";
        (*log) << "'data' may not be null.\n";
      }
      
      if((width + offset_x) > update_texture->width || (height + offset_y) > update_texture->height)
      {
        (*log) << "Incorrect paramaters given to Ogl::texture_update_texture_2d: ";
        (*log) << "Can't update an area larger than the target texture.\n";
      }
    }
    
    return;
  }
  
  glBindTexture(GL_TEXTURE_2D, update_texture->texture_id);
  glTexSubImage2D(GL_TEXTURE_2D,
                  0,
                  offset_x,
                  offset_y,
                  width,
                  height,
                  pixel_format_get_format(update_texture->format),
                  pixel_format_get_type(update_texture->format),
                  data);
  
  // Calling code checks for error.
}



} // ns