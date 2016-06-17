#ifndef VIRTUAL_TEXTURE_TILE_DATA_
#define VIRTUAL_TEXTURE_TILE_DATA_


#include <stdint.h>
#include <stddef.h>


namespace Edge_engine {


struct Virtual_texture_tiles
{
  uint64_t *tile_id;
  uint64_t *least_recently_used;
  uint32_t *texture_index;
  
  size_t size = 0;
}


} // ns


#endif // inc guard