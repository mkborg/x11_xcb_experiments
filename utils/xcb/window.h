#pragma once

#include "xcb/connection.h"
#include "xcb/screen.h"

#include <xcb/xcb.h>

namespace xcb {

/*
    xcb_void_cookie_t xcb_create_window (
            xcb_connection_t *connection,    // Pointer to the xcb_connection_t structure
            uint8_t           depth,         // Depth of the screen
            xcb_window_t      wid,           // Id of the window
            xcb_window_t      parent,        // Id of an existing window that should be the parent of the new window
            int16_t           x,             // X position of the top-left corner of the window (in pixels)
            int16_t           y,             // Y position of the top-left corner of the window (in pixels)
            uint16_t          width,         // Width of the window (in pixels)
            uint16_t          height,        // Height of the window (in pixels)
            uint16_t          border_width,  // Width of the window's border (in pixels)
            uint16_t          _class,
            xcb_visualid_t    visual,
            uint32_t          value_mask,
            const uint32_t   *value_list );
*/

class Window
{
private:
  xcb::Connection& xcb_connection_;
  xcb_window_t window_id_;

public:
  ~Window()
  {
/*
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
*/
  }

  Window(
      xcb::Connection& xcb_connection,
      xcb::Screen& xcb_screen)
    : xcb_connection_(xcb_connection)
//  , window_id_(xcb_generate_id(xcb_connection_))
    , window_id_(xcb_connection_.generate_id())
  {
    xcb_create_window(
        xcb_connection_,		// Connection
        XCB_COPY_FROM_PARENT,		// depth (same as root)
        window_id_,			// window Id
        xcb_screen->root,		// parent window
        0, 0,				// x, y
        150, 150,			// width, height
        10,				// border_width
        XCB_WINDOW_CLASS_INPUT_OUTPUT,	// class
        xcb_screen->root_visual,	// visual
        0, NULL);

    // FIXME: 'assert(xcb_screen_)'
  }

  xcb_void_cookie_t show() const
  {
    return xcb_map_window(xcb_connection_, window_id_);
  }

  xcb_void_cookie_t hide() const
  {
    return xcb_unmap_window(xcb_connection_, window_id_);
  }

  // Move the window on the top of the stack
  xcb_void_cookie_t raise() const
  {
    static const uint32_t values[] = { XCB_STACK_MODE_ABOVE };
    return xcb_configure_window(xcb_connection_, window_id_, XCB_CONFIG_WINDOW_STACK_MODE, values);
  }

  // Move the window on the bottom of the stack
  xcb_void_cookie_t sink() const
  {
    static const uint32_t values[] = { XCB_STACK_MODE_BELOW };
    return xcb_configure_window(xcb_connection_, window_id_, XCB_CONFIG_WINDOW_STACK_MODE, values);
  }
};

} // namespace xcb
