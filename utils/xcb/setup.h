#pragma once

#include "xcb/connection.h"

#include <xcb/xcb.h>

namespace xcb {

class Setup
{
private:
  const xcb_setup_t * xcb_setup_;

public:
  operator const xcb_setup_t * ()
  {
    return xcb_setup_;
  }

  ~Setup()
  {
/*
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
*/
  }

  // Note: 'xcb_get_setup' returns pointer into 'xcb_connection' internals.

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
};

} // namespace xcb
