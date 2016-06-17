#include "ogl_vertex_format.hpp"
#include <assert.h>
#include <string.h>


namespace
{
  uint32_t
  number_of_elements(const Ogl::Attr_type type)
  {
    switch(type)
    {
      case(Ogl::Attr_type::FLOAT1): return 1; break;
      case(Ogl::Attr_type::FLOAT2): return 2; break;
      case(Ogl::Attr_type::FLOAT3): return 3; break;
      case(Ogl::Attr_type::FLOAT4): return 4; break;
      case(Ogl::Attr_type::INT):    return 1; break;
      case(Ogl::Attr_type::UINT):   return 1; break;
    }

    assert(false); // shouldn't have got here.
    return 0; // For waring message.
  }


  GLenum
  gl_type(const Ogl::Attr_type type)
  {
    switch(type)
    {
      case(Ogl::Attr_type::FLOAT1): return GL_FLOAT;         break;
      case(Ogl::Attr_type::FLOAT2): return GL_FLOAT;         break;
      case(Ogl::Attr_type::FLOAT3): return GL_FLOAT;         break;
      case(Ogl::Attr_type::FLOAT4): return GL_FLOAT;         break;
      case(Ogl::Attr_type::INT):    return GL_INT;           break;
      case(Ogl::Attr_type::UINT):   return GL_UNSIGNED_INT;  break;
    }

    assert(false); // shouldn't have got here.
    return 0; // For waring message.
  }
}


namespace Ogl {


void
vertex_format_load(Vertex_format *out_format, const Attribute_desc attr_desc[], const uint32_t number_of_attrs)
{
  if(!out_format)
  {
    assert(out_format); // Must be valid.
    assert(number_of_attrs < MAX_NUMBER_OF_ATTRS); // Max attrs
    assert(number_of_attrs > 0); // We need some attrs to actual make something with.
    return;
  }
  
  // Zero anything that was.
  memset(out_format->attributes, 0, sizeof(out_format->attributes));

  // Build the new format.
  for(uint32_t i = 0; i < number_of_attrs; ++i)
  {
    const Attribute_desc *attr = &attr_desc[i];
    Attribute *out_attr = &out_format->attributes[i];

    strcpy(&out_attr->name[0], &attr->name[0]);
    out_attr->size       = static_cast<uint32_t>(number_of_elements(attr->type));
    out_attr->type       = gl_type(attr->type);
    out_attr->pointer    = out_format->stride;
    out_format->stride  += (number_of_elements(attr->type) * sizeof(gl_type(attr->type)));
    out_format->number_of_attributes += number_of_elements(attr->type);
  }
  
  assert(vertex_format_is_valid(out_format));
}


} // ns