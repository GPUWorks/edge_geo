#include <edge/stage/stage.hpp>
#include <assert.h>


namespace Edge {


struct Stage::Impl
{
  float lat_lon_el[3] = {0.f,0.f,0.f};
  float zoom = 0.f;
};


Stage::Stage()
: m_impl(new Impl)
{
}


Stage::~Stage()
{
}


float
Stage::get_lat() const
{
  assert(m_impl);
  return m_impl->lat_lon_el[0];
}


float
Stage::get_lon() const
{
  assert(m_impl);
  return m_impl->lat_lon_el[1];
}


void
Stage::set_zoom(const float zoom)
{
  assert(m_impl);
  m_impl->zoom = zoom;
}


float
Stage::get_zoom() const
{
  assert(m_impl);
  return m_impl->zoom;
}


} // ns