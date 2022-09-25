#include "xcb/connection.h"

#include "debug.h"
#include "exceptions/runtime_error.h"

#include <xcb/xcb.h>

/*
    Opening and closing the connection to an X server

    An X program first needs to open the connection to the X server, using xcb_connect():

        xcb_connection_t *xcb_connect (
                // if NULL, uses the DISPLAY environment variable
                const char *displayname,
		// returns screen number of the connection; may be NULL if you don't care
                int *screenp);

    To close a connection, it suffices to use:

        void xcb_disconnect (xcb_connection_t *c);
*/

namespace xcb {

Connection::~Connection()
{
  if (xcb_connection_) {
    xcb_disconnect(xcb_connection_);
  }
}

Connection::Connection(const char * display_name)
  : xcb_connection_(xcb_connect(display_name, &screen_))
{
  IPRINTF("screen_=%i", screen_);
  if (xcb_connection_has_error(xcb_connection_)) {
    throw RUNTIME_ERROR_PRINTF("%s() failure", "xcb_connect");
  }
}

} // namespace xcb
