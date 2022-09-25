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
  operator xcb_connection_t * ()
  {
    return xcb_connection_;
  }

  ~Connection();

  Connection(const char * display_name = nullptr);

  int screen() const
  {
    return screen_;
  }

  void flush() const
  {
    xcb_flush(xcb_connection_);
  }

  uint32_t generate_id() const;

  int fd() const
  {
    return xcb_get_file_descriptor(xcb_connection_);
  }
};

} // namespace xcb
