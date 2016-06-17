#include <graphics_api/mesh.hpp>
#include <assert.h>


namespace Graphics_api {


void
mesh_create_new(Mesh *out_mesh,
                const float vbo_data[],
                const uint32_t number_of_vbo_elements,
                const uint32_t ibo_data[],
                const uint32_t number_of_ibo_elements)
{
  assert(out_mesh && vbo_data && number_of_vbo_elements);
  
  Ogl::Vertex_buffer vbo;
  Ogl::vertex_buffer_load(&vbo,
                          vbo_data,
                          sizeof(float) * number_of_vbo_elements,
                          number_of_vbo_elements,
                          false);

  Ogl::Index_buffer ibo;
  
  if(ibo_data)
  {
    assert(false); // not impl.
  }
  
  out_mesh->vbo = vbo;
  out_mesh->ibo = ibo;
}


} // ns