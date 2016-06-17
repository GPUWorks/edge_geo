#include "ogl_vertex_buffer.hpp"
#include "ogl_vertex_format.hpp"
#include "ogl_shader.hpp"
#include <assert.h>
#include <iostream>


namespace Ogl {


void
vertex_buffer_load(Vertex_buffer *out_vbo,
                   const void *vbo_buffer,
                   const uint32_t byte_size_of_vbo,
                   const uint32_t number_of_individual_elements,
                   const bool is_dynamic)
{
  assert(out_vbo);
  
  glGenBuffers(1, &out_vbo->vertex_buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, out_vbo->vertex_buffer_id);
  glBufferData(GL_ARRAY_BUFFER, byte_size_of_vbo, vbo_buffer, is_dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  if(out_vbo->vertex_buffer_id)
  {
    out_vbo->number_of_entries = static_cast<uint32_t>(number_of_individual_elements);
  }

  assert(vertex_buffer_is_valid(*out_vbo));
  Ogl::error_check("Loading vbo", &std::cout);
}


void
vertex_buffer_bind(const Vertex_buffer vbo,
                   const Vertex_format *vert_fmt,
                   const Shader *shd)
{
  assert(vertex_buffer_is_valid(vbo));

  glBindBuffer(GL_ARRAY_BUFFER, vbo.vertex_buffer_id);
  Ogl::error_check("Bind vertex buffer", &std::cout);
  
  // Vertex Format
  {
    for(std::uint32_t i = 0; i < vert_fmt->number_of_attributes; ++i)
    {
      const GLint NOT_USED = -1;
      const Attribute *attrib = &vert_fmt->attributes[i];

      GLint index = glGetAttribLocation(shd->program_id, attrib->name);

      if(index != NOT_USED)
      {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              static_cast<GLint>(attrib->size),
                              attrib->type,
                              GL_FALSE,
                              vert_fmt->stride,
                              (void*)attrib->pointer);

        Ogl::error_check("Applying vertex format", &std::cout);
      }
    }
  }
}


} // ns