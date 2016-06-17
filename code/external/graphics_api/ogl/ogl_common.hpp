#ifndef COMMON_INCLUDED_57928899_C288_49E0_8694_6E85E36592EA
#define COMMON_INCLUDED_57928899_C288_49E0_8694_6E85E36592EA


#include <ostream>

#ifdef _WIN32
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#define LOG_GL_ERROR(msg)

#include <iostream> // for error stream this needs to change.
#include <utilities/logging.hpp>

namespace Ogl {


/*!
  Resets the gl states to the applications default.
*/
void
default_state();


/*!
  Sugar function to for clear color
*/
void
clear_color(const float r = 0,
            const float g = 0,
            const float b = 0,
            const float a = 0);


/*!
  Sugar function to clear attached buffer
  \param color If true clears the attached color buffer.
  \param depth If true clears the attached depth buffer.
*/
void
clear(const bool color, const bool depth);


/*!
  Initialize vao
*/
void
vao_init();


/*!
  Checks glGetError, if an error is found it will push it out
  in the stream that was provided.
*/
void
error_check(const char* msg, std::ostream *stream);


void
error_output(const char *msg);

/*!
  Clears any pending error.
*/
void
error_clear();


} // ns


#endif // inc guard