#ifndef INDEX_BUFFER_INCLUDED_54694EF4_48CC_4300_956B_4DAB470651EB
#define INDEX_BUFFER_INCLUDED_54694EF4_48CC_4300_956B_4DAB470651EB


#include "ogl_common.hpp"
#include <stdint.h>


namespace Ogl {


/*!
  Structure for GL index buffer.
*/
struct Index_buffer
{
  GLuint          index_buffer_id = 0;
  uint32_t        number_of_indices = 0;
}; // struct


/*
  Creates an Index buffer.
  \param out_ibo The index buffer object to write to.
  \param index[] The index array.
  \param index_count The number if indices in the array.
*/
void
index_buffer_load(Index_buffer *out_ibo,
                  const uint32_t index[],
                  const uint32_t index_count);
  

/*
  Bind an index buffer.
  \param ibo The index buffer you wish to bind.
*/
void
index_buffer_bind(const Index_buffer ibo);


/*
  Draw with an index buffer.
  This will bind the ibo, no need to bind it perviously.
  \param ibo the index buffer to draw.
 
*/
void
index_buffer_draw(const GLenum primitive, const Index_buffer ibo);


/*
  Simple check to see if an ibo is valid.
  This is just a simple check to see if it has an id that isn't zero.
  \param ibo The ibo you wish to check.
*/
inline bool
index_buffer_is_valid(const Index_buffer ibo)
{
  return ibo.index_buffer_id > 0;
}


} // ns


#endif // inc guard