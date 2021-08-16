#pragma once

#include "xcb_connection.h"

#include <xcb/xcb.h>

namespace xcb {

class Setup
{
private:
  const xcb_setup_t * xcb_setup_;

public:
  ~Setup()
  {
/*
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
*/
  }

  Setup(xcb_connection_t * xcb_connection)
    : xcb_setup_(xcb_get_setup(xcb_connection))
  {
    // FIXME: 'assert(xcb_setup_)'
  }

  Setup(xcb::Connection& xcb_connection)
    : xcb_setup_(xcb_get_setup(static_cast<xcb_connection_t *>(xcb_connection)))
  {
    // FIXME: 'assert(xcb_setup_)'
  }

  operator const xcb_setup_t * ()
  {
    return xcb_setup_;
  }
};

} // namespace xcb
