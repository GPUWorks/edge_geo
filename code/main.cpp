#include <stdio.h>
#include <graphics_api/ogl/ogl_shader.hpp>
#include <graphics_api/ogl/ogl_shader_uniform.hpp>
#include <graphics_api/ogl/ogl_vertex_format.hpp>
#include <graphics_api/initialize.hpp>
#include <graphics_api/clear.hpp>
#include <graphics_api/mesh.hpp>
#include <graphics_api/ogl/ogl_texture.hpp>
#include <sdl-wrapper/window.hpp>
#include <sdl-wrapper/ogl_context.hpp>
#include <sdl-wrapper/input.hpp>
#include <sdl-wrapper/message_pump.hpp>
#include <curl/curl.h>
#include <edge/stage/stage.hpp>
#include <edge/stage/stage_utils.hpp>


#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl_gl3.h>


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;\
}


namespace Slippy_utils {


void
get_tile_number_from_lat_lon_zoom(const float lat_degrees,
                                  const float lon_degrees,
                                  const float zoom,
                                  uint32_t out_tile[2])
{
  const float lat_radians = lat_degrees / 180.f * 3.142f;
  const float n = powf(2.0, zoom);

  const float x_tile = (lon_degrees + 180.f) / 360.f * n;
//  const float y_tile = (1.f - log(tanf(lat_degrees * 3.142 / 180.f) + 1.f / cosf(lat_degrees * 3.142 / 180.f)) / 3.142f) / 2.f * n;
  const float y_tile = (1.0 - log( tan(lat_degrees * M_PI/180.0) + 1.0 / cos(lat_degrees * M_PI/180.0)) / M_PI) / 2.f * pow(2.0, zoom);
  
  out_tile[0] = static_cast<uint32_t>(x_tile);
  out_tile[1] = static_cast<uint32_t>(y_tile);
  
//   lat_rad = lat_deg/180 * Math::PI
//  n = 2.0 ** zoom
//  x = ((lng_deg + 180.0) / 360.0 * n).to_i
//  y = ((1.0 - Math::log(Math::tan(lat_rad) + (1 / Math::cos(lat_rad))) / Math::PI) / 2.0 * n).to_i
}


int lat2tiley(float lat, int z)
{ 
	return (int)(floor((1.0 - log( tan(lat * M_PI/180.0) + 1.0 / cos(lat * M_PI/180.0)) / M_PI) / 2.0 * pow(2.0, z))); 
}


} // ns


namespace Network {


inline void
download_tile(const uint32_t tile_x,
              const uint32_t tile_y,
              const uint32_t zoom)
{
  char url[1024];
  char output[FILENAME_MAX];
  
  const char * api_key = "pk.eyJ1IjoicGhpbGNrIiwiYSI6ImNpZ2VyaHp3NzJnaHh1aWx5MGV0Yjkyb2EifQ.RwoRhhhoR8UuhsGMkOpANw";
  
  sprintf(url, "https://api.mapbox.com/v4/mapbox.streets/%d/%d/%d.png?access_token=%s", zoom, tile_x, tile_y, api_key);
  
  sprintf(output, "/Users/phil0005/Dev/edge/assets/download/images/%d-%d-%d.png", zoom, tile_x, tile_y);

  CURL *curl;
  FILE *fp;
  CURLcode res;

  curl = curl_easy_init();
  if (curl)
  {
    fp = fopen(output,"wb");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);
    /* always cleanup */
    curl_easy_cleanup(curl);
    fclose(fp);
  }
}


} // ns

#include <OpenGL/gl3.h>

int
main()
{
  uint32_t boo[2];
  Slippy_utils::get_tile_number_from_lat_lon_zoom(-80, -45, 1, boo);
  
  // Create a window and context
  sdl::window win(512, 512, false);
  sdl::ogl_context ogl(win);
  
  sdl::message_callback_register([&](const SDL_Event &event) -> bool
  {
    return ImGui_ImplSdlGL3_ProcessEvent(&event);
  });
  
  ImGui_ImplSdlGL3_Init(win.get_sdl_window());
  
  // Initialize Ogl
  Graphics_api::initialize();
  Graphics_api::clear_color_set(0.3f, 0.4f, 0.3f);
  
  GLint size;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);

  
  // Create a mesh
  Graphics_api::Mesh mesh;
  {
    constexpr uint32_t number_of_verts = 30; // not really verts are they Phil!
  
    float vbo_data[number_of_verts] = {
      -0.5f, +0.5f, 0.f, 0.f, 0.f,
      +0.5f, -0.5f, 0.f, 1.f, 1.f,
      -0.5f, -0.5f, 0.f, 0.f, 1.f,
      
      -0.5f, +0.5f, 0.f, 0.f, 0.f,
      +0.5f, +0.5f, 0.f, 1.f, 0.f,
      +0.5f, -0.5f, 0.f, 1.f, 1.f,
    };
    
    Graphics_api::mesh_create_new(&mesh, vbo_data, number_of_verts, nullptr, 0);
  }
  
  // Create map mesh
  Graphics_api::Mesh map_mesh;
  {
    float vbo_data[] = {
      // QUAD
      -1.0f, +1.0f, 0.f, 0.f, 0.f,
      +0.0f, -0.0f, 0.f, 1.f, 1.f,
      -1.0f, -0.0f, 0.f, 0.f, 1.f,
      
      -1.0f, +1.0f, 0.f, 0.f, 0.f,
      +0.0f, +1.0f, 0.f, 1.f, 0.f,
      +0.0f, -0.0f, 0.f, 1.f, 1.f,
      
      // QUAD
      -1.0f, +0.0f, 0.f, 0.f, 0.f,
      +0.0f, -1.0f, 0.f, 1.f, 1.f,
      -1.0f, -1.0f, 0.f, 0.f, 1.f,
      
      -1.0f, +0.0f, 0.f, 0.f, 0.f,
      +0.0f, +0.0f, 0.f, 1.f, 0.f,
      +0.0f, -1.0f, 0.f, 1.f, 1.f,

      // QUAD
      -0.0f, +1.0f, 0.f, 0.f, 0.f,
      +1.0f, -0.0f, 0.f, 1.f, 1.f,
      -0.0f, -0.0f, 0.f, 0.f, 1.f,
      
      -0.0f, +1.0f, 0.f, 0.f, 0.f,
      +1.0f, +1.0f, 0.f, 1.f, 0.f,
      +1.0f, -0.0f, 0.f, 1.f, 1.f,

      // QUAD
      -0.0f, +0.0f, 0.f, 0.f, 0.f,
      +1.0f, -1.0f, 0.f, 1.f, 1.f,
      -0.0f, -1.0f, 0.f, 0.f, 1.f,
      
      -0.0f, +0.0f, 0.f, 0.f, 0.f,
      +1.0f, +0.0f, 0.f, 1.f, 0.f,
      +1.0f, -1.0f, 0.f, 1.f, 1.f,
      };
    
    Graphics_api::mesh_create_new(&map_mesh, vbo_data, 30 * 4, nullptr, 0);
  }
  
  // Shader
  Ogl::Shader shader;
  {
    constexpr const char *vs_shader = R"(
      // Vertex Shader.
      #version 150

      #define SIZE_OF_VT 4096
      #define SIZE_OF_TILE 256
    
      float g_offset = 1.0 / (SIZE_OF_VT / SIZE_OF_TILE);

      in vec3 vs_in_position;
      in vec2 vs_in_tex_coord;
    
      uniform float uni_zoom = 1.0;
      uniform int uni_offset_lookup[128];
    
      out vec2 ps_in_tex_coord;

      void main()
      {
        float zoom_to_apply = 1.0 + fract(uni_zoom);
        
        gl_Position = vec4(vs_in_position * zoom_to_apply, 1.0);
        
        int index = (gl_VertexID / 6);
        
        float tile_offset = uni_offset_lookup[index] * g_offset;
        
        vec2 tex_coords = vec2((vs_in_tex_coord.x * g_offset) + tile_offset, vs_in_tex_coord.y * g_offset);
        
        ps_in_tex_coord = tex_coords;
      }
    )";
    
    constexpr const char *ps_shader = R"(
    
      // Frag shader
     #version 150

      in vec2 ps_in_tex_coord;
    
      uniform sampler2D uni_texture;
    
      out vec4 outColor;

      void main()
      {
//        outColor = vec4(ps_in_tex_coord, 1.0, 1.0);
        outColor = texture(uni_texture, ps_in_tex_coord);
      }
    )";
    
    Ogl::shader_create(&shader, vs_shader, "", ps_shader);
    assert(Ogl::shader_is_valid(&shader));
  }
  
  Ogl::error_check("Compile shader", &std::cout);
  
  // Vert Fmt
  Ogl::Vertex_format vert_fmt;
  {
    Ogl::Attribute_desc desc[] = {
      Ogl::Attribute_desc{"vs_in_position",  Ogl::Attr_type::FLOAT3},
      Ogl::Attribute_desc{"vs_in_tex_coord", Ogl::Attr_type::FLOAT2},
    };
  
    Ogl::vertex_format_load(&vert_fmt, desc, 2);
  }
  
  Ogl::error_check("Vert Attr", &std::cout);
  
  // Shader uni
  Ogl::Uniform tex_uni;
  Ogl::Uniform index_array;
  {
    Ogl::Shader_uniforms unis;
    Ogl::shader_uniforms_retrive(&unis, &shader);
    
    Ogl::shader_uniforms_get_uniform_index(&tex_uni, &unis, "uni_texture");
    Ogl::shader_uniforms_get_uniform_index(&index_array, &unis, "uni_offset_lookup[0]");
  }
  
  Ogl::error_check("Texture Uni", &std::cout);

  // Texture Store
  
  Ogl::Texture texture_store;
  uint32_t curr_slot = 0;
  {
    const uint32_t width = 1 << 12;
    const uint32_t height = width;
    uint8_t *data = new uint8_t[width * height * 3];
  
    Ogl::texture_create_2d(&texture_store, width, height, GL_RGB, data, false);
    assert(Ogl::texture_is_valid(&texture_store));
  }
  
  // Texture
  Ogl::Texture texture;
  {
    int width, height, comp;
    auto data = stbi_load("/Users/phil0005/Dev/edge/assets/images/0.png", &width, &height, &comp, STBI_rgb);
    Ogl::texture_create_2d(&texture, width, height, GL_RGB, data, false);
    
    Ogl::texture_update_texture_2d(&texture_store, 0, 0, width, height, data, &std::cout);
    assert(Ogl::texture_is_valid(&texture_store));
    curr_slot++;
    
    auto err = glGetError();
    if(err)
    {
      std::cout << err << std::endl;
    }
    
    STBI_FREE(data);
    
    
    assert(Ogl::texture_is_valid(&texture));
  }
  
  Ogl::error_check("Texture Load", &std::cout);
  
  
  // Test download range.
  Edge::Stage stage;
  stage.set_zoom(2);
  {
    float range[4];
    Edge::Stage_utils::get_lat_lon_range(stage, range);
    
    uint32_t top_left_tile[2];
    Slippy_utils::get_tile_number_from_lat_lon_zoom(range[2], range[1], stage.get_zoom(), top_left_tile);
    
    uint32_t bot_right_tile[2];
    Slippy_utils::get_tile_number_from_lat_lon_zoom(range[0], range[3], stage.get_zoom(), bot_right_tile);
    
    for(int x = top_left_tile[0]; x <= bot_right_tile[0]; ++x) {
      for(int y = top_left_tile[1]; y <= bot_right_tile[1]; ++y)
      {
        printf("Tile: %d, %d, %d \n", x, y, static_cast<uint32_t>(stage.get_zoom()));
//        Network::download_tile(x, y, floorf(stage.get_zoom()));
        
        int tx = curr_slot % (256 * 4);
        int ty = curr_slot / (256 * 4);
        
        Ogl::Texture loading;
        int width, height, comp;
        
        char file[2048];
        sprintf(file, "/Users/phil0005/Dev/edge/assets/download/images/%d-%d-%d.png", static_cast<uint32_t>(stage.get_zoom()), x, y);
        
        auto data = stbi_load(file, &width, &height, &comp, STBI_rgb);
        Ogl::texture_create_2d(&loading, width, height, GL_RGB, data, false);
        
        Ogl::texture_update_texture_2d(&texture_store, tx * 256, ty * 256, 256, 256, data, &std::cout);
        assert(Ogl::texture_is_valid(&texture_store));
        
        curr_slot++;
        
      }
    }
  }
  
  
  int offset_index[] = {1,2,3,4,5,6,7,8,9};
  
  
  while(!win.wants_to_quit())
  {
    Graphics_api::clear(Graphics_api::Clear_flag::depth | Graphics_api::Clear_flag::color);
    sdl::message_pump();
    
    ImGui_ImplSdlGL3_NewFrame(win.get_sdl_window());
    
    Ogl::shader_bind(&shader);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    Ogl::shader_uniforms_apply(tex_uni, (void*)&texture_store.texture_id);
    Ogl::shader_uniforms_apply(index_array, (void*)offset_index);
    
    Ogl::vertex_buffer_bind(map_mesh.vbo, &vert_fmt, &shader);
  
    glDrawArrays(GL_TRIANGLES, 0, 24);
    
    win.flip_buffer();
  }
  
  return 0;
}