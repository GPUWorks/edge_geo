#ifndef MESH_INCLUDED_91DAFBDD_42F8_422B_BA7B_EE592DBC2CEA
#define MESH_INCLUDED_91DAFBDD_42F8_422B_BA7B_EE592DBC2CEA


#include <graphics_api/gfx_common.hpp>
#include <graphics_api/ogl/ogl_vertex_buffer.hpp>
#include <graphics_api/ogl/ogl_index_buffer.hpp>
#include <stdint.h>


namespace Graphics_api {


struct Mesh
{
  API_TYPE::Vertex_buffer vbo;
  API_TYPE::Index_buffer ibo;
};


void
mesh_create_new(Mesh *out_mesh,
                const float vbo_data[],
                const uint32_t number_of_vbo_elements,
                const uint32_t ibo_data[] = nullptr,
                const uint32_t number_of_ibo_elements = 0);


} // ns


#endif // inc guard