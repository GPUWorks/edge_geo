#!lua

edge_project_data = {

  name     = "Edge",
  kind     = "WindowedApp",
  language = "C++",
  location = make.get_proj_root(),

  src_files = {
    make.get_proj_root() .. "../code/**.hpp",
    make.get_proj_root() .. "../code/**.inl",
    make.get_proj_root() .. "../code/**.cpp",
    make.get_proj_root() .. "../code/**.mm",
    make.get_proj_root() .. "../code/**.h",
    make.get_proj_root() .. "../code/**.c",
    make.get_proj_root() .. "../code/**.m",
    make.get_proj_root() .. "../code/**.md",
  },

  src_files_exclude_windows = {
    make.get_proj_root() .. "../code/external/utilities/utilities/directory_nix.cpp",
    make.get_proj_root() .. "../code/external/utilities/utilities/directory_mac.mm",
  },

  src_files_exclude_macosx = {
    make.get_proj_root() .. "../code/external/utilities/utilities/directory_win.cpp",
  },

  inc_dirs = {
    make.get_proj_root() .. "../code/",
    make.get_proj_root() .. "../code/external/",
  },

  inc_dirs_macosx = {
    "/usr/local/include/",
  },

  lib_dirs_macosx = {
    "/usr/local/lib/",
  },

  links = {
    "OpenGL.framework",
    "CoreFoundation.framework",
    "Foundation.framework",
  },

  linkoptions = {
    "-lsdl2",
    "-lcurl",
  },
}
