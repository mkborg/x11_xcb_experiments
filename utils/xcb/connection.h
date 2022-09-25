#pragma once

#include <xcb/xcb.h>

/*
    'screen' is number after 'dot' ('.') symbol in 'display' string or
    'DISPLAY' environment variable:

        DISPLAY=":0.0"
*/

namespace xcb {

class Connection
{
private:
  xcb_connection_t * xcb_connection_;
  int screen_;

public:
  ~Connection();

  Connection(const char * display_name = nullptr);

  operator xcb_connection_t * ()
  {
    return xcb_connection_;
  }

  int screen()
  {
    return screen_;
  }

  void flush() const
  {
    xcb_flush(xcb_connection_);
  }

  xcb_window_t generate_id() const
  {
    return xcb_generate_id(xcb_connection_);
  }
};

} // namespace xcb
