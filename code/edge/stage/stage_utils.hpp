#ifndef STAGE_UTILS_INCLUDED_
#define STAGE_UTILS_INCLUDED_


#include <edge/edge_fwd.hpp>


namespace Edge {
namespace Stage_utils {


/*!
  Returns the top-left and bot-right lat lon.
*/
void
get_lat_lon_range(class Stage &stage, float out_lat_lon_range[4]);


} // ns
} // ns


#endif // inc guard