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

/*
  typedef enum xcb_event_mask_t {
    XCB_EVENT_MASK_NO_EVENT = 0,
    XCB_EVENT_MASK_KEY_PRESS = 1,
    XCB_EVENT_MASK_KEY_RELEASE = 2,
    XCB_EVENT_MASK_BUTTON_PRESS = 4,
    XCB_EVENT_MASK_BUTTON_RELEASE = 8,
    XCB_EVENT_MASK_ENTER_WINDOW = 16,
    XCB_EVENT_MASK_LEAVE_WINDOW = 32,
    XCB_EVENT_MASK_POINTER_MOTION = 64,
    XCB_EVENT_MASK_POINTER_MOTION_HINT = 128,
    XCB_EVENT_MASK_BUTTON_1_MOTION = 256,
    XCB_EVENT_MASK_BUTTON_2_MOTION = 512,
    XCB_EVENT_MASK_BUTTON_3_MOTION = 1024,
    XCB_EVENT_MASK_BUTTON_4_MOTION = 2048,
    XCB_EVENT_MASK_BUTTON_5_MOTION = 4096,
    XCB_EVENT_MASK_BUTTON_MOTION = 8192,
    XCB_EVENT_MASK_KEYMAP_STATE = 16384,
    XCB_EVENT_MASK_EXPOSURE = 32768,
    XCB_EVENT_MASK_VISIBILITY_CHANGE = 65536,
    XCB_EVENT_MASK_STRUCTURE_NOTIFY = 131072,
    XCB_EVENT_MASK_RESIZE_REDIRECT = 262144,
    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY = 524288,
    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT = 1048576,
    XCB_EVENT_MASK_FOCUS_CHANGE = 2097152,
    XCB_EVENT_MASK_PROPERTY_CHANGE = 4194304,
    XCB_EVENT_MASK_COLOR_MAP_CHANGE = 8388608,
    XCB_EVENT_MASK_OWNER_GRAB_BUTTON = 16777216
  } xcb_event_mask_t;
*/
  Window(
      xcb::Connection& xcb_connection,
      xcb::Screen& xcb_screen)
    : xcb_connection_(xcb_connection)
//  , window_id_(xcb_generate_id(xcb_connection_))
    , window_id_(xcb_connection_.generate_id())
  {
    const xcb_window_t parent_window_id = xcb_screen->root;
    xcb_create_window(
        xcb_connection_,		// Connection
        XCB_COPY_FROM_PARENT,		// depth (same as root)
        window_id_,			// window Id
        parent_window_id,		// parent window
        0, 0,				// x, y
        150, 150,			// width, height
        10,				// border_width
        XCB_WINDOW_CLASS_INPUT_OUTPUT,	// class
        xcb_screen->root_visual,	// visual
        0, NULL);

    // FIXME: 'assert(xcb_screen_)'
  }

  xcb_void_cookie_t
  change_attributes(uint32_t value_mask, const void * value_list) const
  {
    return xcb_change_window_attributes(xcb_connection_, window_id_, value_mask, value_list);
  }

  xcb_void_cookie_t show() const
  {
    return xcb_map_window(xcb_connection_, window_id_);
  }

  xcb_void_cookie_t hide() const
  {
    return xcb_unmap_window(xcb_connection_, window_id_);
  }

  xcb_void_cookie_t
  configure(uint16_t value_mask, const uint32_t *value_list) const
  {
    return xcb_configure_window(xcb_connection_, window_id_, value_mask, value_list);
  }

  // Move the window on the top of the stack
  xcb_void_cookie_t raise() const
  {
    static const uint32_t values[] = { XCB_STACK_MODE_ABOVE };
    return configure(XCB_CONFIG_WINDOW_STACK_MODE, values);
  }

  // Move the window on the bottom of the stack
  xcb_void_cookie_t sink() const
  {
    static const uint32_t values[] = { XCB_STACK_MODE_BELOW };
    return configure(XCB_CONFIG_WINDOW_STACK_MODE, values);
  }

  xcb_void_cookie_t move(uint32_t x, uint32_t y) const
  {
    const uint32_t values[] = { x, y };
    return configure(XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y, values);
  }

  xcb_void_cookie_t resize(uint32_t size_x, uint32_t size_y) const
  {
    const uint32_t values[] = { size_x, size_y };
    return configure(XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT, values);
  }
};

} // namespace xcb
