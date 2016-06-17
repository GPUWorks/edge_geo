#!lua

package.path = '../../core/projects/?.lua;' .. package.path
package.path = '../../premake_data/?.lua;' .. package.path

require "premake_data"

dofile("edge_project.lua")


-- Solution data? Should this contain the the project names?
solution_data = {

  name = "Edge-Solution"

}

project_defaults = {

  buildoptions_macosx = {
    "-std=c++14",
    "-stdlib=libc++",
  },

  define = {
    EDGE_APP,
  },

  define_macosx = {
    EDGE_APP_MACOS,
  },
}

-- Generates the premake code calls.
make.create_solution(solution_data,
                     project_defaults,
                     edge_project_data);
