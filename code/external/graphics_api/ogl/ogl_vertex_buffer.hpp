#ifndef VERTEX_BUFFER_INCLUDED_6B0396A7_C8ED_4C71_82E3_5D6D1D65650C
#define VERTEX_BUFFER_INCLUDED_6B0396A7_C8ED_4C71_82E3_5D6D1D65650C


#include "ogl_common.hpp"
#include "ogl_fwd.hpp"
#include <stdint.h>


namespace Ogl {


/*!
  Structure for GL vertex buffer.
*/
struct Vertex_buffer
{
  GLuint    vertex_buffer_id  = 0;
  uint32_t  number_of_entries = 0;
};


/*!
  Creates a Vertex Buffer.
  \param out_vbo Where to write the details.
  \param vbo_buffer The buffer of data.
  \param byte_size_of_vbo the sizeof the buffer in bytes.
  \param number_of_individual_elements How many elements are contained in the buffer.
  \param is_dynamic Is the mesh going to be updated on the cpu.
*/
void
vertex_buffer_load(Vertex_buffer *out_vbo,
                   const void *vbo_buffer,
                   const uint32_t byte_size_of_vbo,
                   const uint32_t number_of_individual_elements,
                   const bool is_dynamic);


/*!
  Binds the vbo to the shader.
  \param vbo to bind.
  \param vert_fmt vertex format.
  \param shd shader to bind to.
*/
void
vertex_buffer_bind(const Vertex_buffer vbo,
                   const Vertex_format *vert_fmt,
                   const Shader *shd);


/*!
  Checks to see if a vbo is valid.
  This only checks that the vbo_id has been set.
  \param vbo to check.
*/
inline bool
vertex_buffer_is_valid(const Vertex_buffer vbo)
{
  return vbo.vertex_buffer_id > 0;
}


} // ns


#endif // inc guard