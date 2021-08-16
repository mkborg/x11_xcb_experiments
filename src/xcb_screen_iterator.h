#pragma once

#include <xcb/xcb.h>

namespace xcb {
namespace screen {

class Iterator
{
private:
  xcb_screen_iterator_t xcb_screen_iterator_;

public:
  ~Iterator()
  {
/*
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
*/
  }

  Iterator(const xcb_setup_t * xcb_setup)
    : xcb_screen_iterator_(xcb_setup_roots_iterator(xcb_setup))
  {
    // FIXME: 'assert(xcb_screen_iterator_)'
  }

  operator bool()
  {
    return xcb_screen_iterator_.data;
  }

  void operator ++()
  {
    xcb_screen_next(&xcb_screen_iterator_);
  }

  xcb_screen_t * screen() const
  {
    return xcb_screen_iterator_.data;
  }
};

} // namespace screen
} // namespace xcb
