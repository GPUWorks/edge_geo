#ifndef STAGE_INCLUDED_
#define STAGE_INCLUDED_


#include <memory>


namespace Edge {


class Stage
{
public:

  explicit      Stage();
                ~Stage();
  
  float         get_lat() const;
  float         get_lon() const;
  
  void          set_zoom(const float zoom);
  float         get_zoom() const;

private:

  struct Impl;
  std::unique_ptr<Impl> m_impl;

};


} // ns


#endif // inc guard
