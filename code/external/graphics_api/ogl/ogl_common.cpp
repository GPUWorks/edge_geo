#include "ogl_common.hpp"




namespace Ogl {


void
default_state()
{
  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);
  glFrontFace(GL_CCW);
}


void
clear_color(const float r,
            const float g,
            const float b,
            const float a)
{
  glClearColor(r, g, b, a);
}


void
vao_init()
{
  static GLuint vao(0);

  if (!vao)
  {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
  }
}


void
clear(const bool color, const bool depth)
{
  GLint clear = 0;

  if (color) { clear |= GL_COLOR_BUFFER_BIT; }
  if (depth) { clear |= GL_DEPTH_BUFFER_BIT; }

  glClear(clear);
}



/*!
  Checks glGetError, if an error is found it will push it out
  in the stream that was provided.
*/
void
error_check(const char* msg, std::ostream *stream)
{
  //LOG_DEPRECATED;

  if(stream) // Check stream first, if none given we don't want to clear the error.
  {
    const auto err_id = glGetError();

    if(err_id != GL_NO_ERROR)
    {
      (*stream) << err_id << " " << msg << "\n";
    }
  }
}


/*!
  Clears any pending error.
*/
void
error_clear()
{
  while(glGetError()) {}
}


} // ns