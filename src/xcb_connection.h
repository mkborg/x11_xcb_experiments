#pragma once

#include <xcb/xcb.h>

/*
    Opening and closing the connection to an X server

    An X program first needs to open the connection to the X server, using xcb_connect():

        xcb_connection_t *xcb_connect (
                const char *displayname,  // if NULL, uses the DISPLAY environment variable
                int *screenp );    // returns the screen number of the connection; can provide NULL if you don't care

    To close a connection, it suffices to use:

        void xcb_disconnect (xcb_connection_t *c);
*/

namespace xcb {

class Connection
{
private:
  xcb_connection_t * xcb_connection_;
  int screen_;

public:
  ~Connection()
  {
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
  }

  Connection(const char * display_name = nullptr)
    : xcb_connection_(xcb_connect(display_name, &screen_))
  {
    // FIXME: 'assert(xcb_connection_)'
  }

  operator xcb_connection_t * ()
  {
    return xcb_connection_;
  }

  int screen()
  {
    return screen_;
  }
};

} // namespace xcb
