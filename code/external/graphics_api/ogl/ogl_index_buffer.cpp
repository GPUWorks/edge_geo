#include "ogl_index_buffer.hpp"


namespace Ogl {


void
index_buffer_load(Index_buffer *out_ibo,
                  const uint32_t index[],
                  const uint32_t index_count)
{
  memset(out_ibo, 0, sizeof(Index_buffer));

  out_ibo->number_of_indices = index_count;

  glGenBuffers(1, &out_ibo->index_buffer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out_ibo->index_buffer_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * index_count, index, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  error_check("Creating Index buffer", &std::cout);
}
  
  
  
void
index_buffer_bind(const Index_buffer ibo)
{
  if(index_buffer_is_valid(ibo))
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo.index_buffer_id);
    error_check("Binding Index buffer", &std::cout);
  }
}


void
index_buffer_draw(const GLenum primitive, const Index_buffer ibo)
{
  if(index_buffer_is_valid(ibo))
  {
    index_buffer_bind(ibo);
    glDrawElements(GL_TRIANGLES, ibo.number_of_indices, GL_UNSIGNED_INT, 0);
  }
}


} // ns