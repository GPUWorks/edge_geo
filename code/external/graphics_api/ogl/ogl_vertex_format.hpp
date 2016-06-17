#ifndef OGL_VERTEX_FORMAT_INCLUDED_2A5ADC43_7779_46FF_B20A_55C8CD781A97
#define OGL_VERTEX_FORMAT_INCLUDED_2A5ADC43_7779_46FF_B20A_55C8CD781A97


#include "ogl_common.hpp"
#include <stdint.h>
#include <stddef.h>
#include <assert.h>


#define MAX_NUMBER_OF_ATTRS 8


namespace Ogl {


// TODO: This could move up a level?
enum class Attr_type
{
  FLOAT1,
  FLOAT2,
  FLOAT3,
  FLOAT4,
  INT,
  UINT,
};


// TODO: Could this move up a level?
struct Attribute_desc
{
  char        name[32];
  Attr_type   type;
};


/*!
  Structure for GL attribute.
*/
struct Attribute
{
  char          name[32];
  GLenum        type    = GL_NONE;
  uint32_t      size    = 0;
  uint32_t      pointer = 0;
};


/*!
  Structure for GL vertex attribute.
*/
struct Vertex_format
{
  Attribute   attributes[MAX_NUMBER_OF_ATTRS];
  uint32_t    stride               = 0;
  uint32_t    number_of_attributes = 0;
};


/*!
  Create an ogl vertex format.
  \param out_format is the result.
  \param attr_desc[] An array of vertex attributes.
  \param number_of_attributes How many attributes in the array.
*/
void
vertex_format_load(Vertex_format *out_format,
                   const Attribute_desc attr_desc[],
                   const uint32_t number_of_attributes);


/*!
  Checks to see if the vertex format is valid.
  This only checks that stride > 0.
  \return true if the format is valid.
*/
inline bool
vertex_format_is_valid(Vertex_format *vert_fmt)
{
  assert(vert_fmt);
  return vert_fmt->stride > 0;
}

  
} // ns


#endif // inc guard