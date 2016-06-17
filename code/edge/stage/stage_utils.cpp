#include <edge/stage/stage_utils.hpp>
#include <edge/stage/stage.hpp>


namespace Edge {
namespace Stage_utils {


void
get_lat_lon_range(class Stage &stage, float out_lat_lon_range[4])
{
  const uint32_t zoom = 1 << static_cast<uint32_t>(stage.get_zoom());
  
  out_lat_lon_range[0] = stage.get_lat() - (90 / zoom);
  out_lat_lon_range[1] = stage.get_lon() - (180 / zoom);
  
  out_lat_lon_range[2] = stage.get_lat() + (90 / zoom);
  out_lat_lon_range[3] = stage.get_lon() + (180 / zoom);
}


} // ns
} // ns