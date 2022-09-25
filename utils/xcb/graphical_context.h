#pragma once

#include "xcb/connection.h"
#include "xcb/screen.h"

#include <xcb/xcb.h>

/*
    xcb_void_cookie_t xcb_create_gc(
        xcb_connection_t *c,
        xcb_gcontext_t    cid,
        xcb_drawable_t    drawable,
        uint32_t          value_mask,
        const uint32_t   *value_list );

    xcb_void_cookie_t xcb_change_gc(
        xcb_connection_t *c,            // The XCB Connection
        xcb_gcontext_t    gc,           // The Graphic Context
        uint32_t          value_mask,   // Components of the Graphic Context that have to be set
        const uint32_t   *value_list ); // Value as specified by value_mask

    'valuemask' parameter could take any combination of these masks from the xcb_gc_t enumeration:

        XCB_GC_FUNCTION
        XCB_GC_PLANE_MASK
        XCB_GC_FOREGROUND
        XCB_GC_BACKGROUND
        XCB_GC_LINE_WIDTH
        XCB_GC_LINE_STYLE
        XCB_GC_CAP_STYLE
        XCB_GC_JOIN_STYLE
        XCB_GC_FILL_STYLE
        XCB_GC_FILL_RULE
        XCB_GC_TILE
        XCB_GC_STIPPLE
        XCB_GC_TILE_STIPPLE_ORIGIN_X
        XCB_GC_TILE_STIPPLE_ORIGIN_Y
        XCB_GC_FONT
        XCB_GC_SUBWINDOW_MODE
        XCB_GC_GRAPHICS_EXPOSURES
        XCB_GC_CLIP_ORIGIN_X
        XCB_GC_CLIP_ORIGIN_Y
        XCB_GC_CLIP_MASK
        XCB_GC_DASH_OFFSET
        XCB_GC_DASH_LIST
        XCB_GC_ARC_MODE
*/
namespace xcb {
namespace graphical {

class Context
{
private:
  xcb::Connection& xcb_connection_;
  xcb_gcontext_t xcb_gcontext_;

public:
  operator xcb_gcontext_t() const
  {
    return xcb_gcontext_;
  }

  ~Context()
  {
/*
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
*/
  }

  Context(
      xcb::Connection& xcb_connection,
      xcb::Screen& xcb_screen)
    : xcb_connection_(xcb_connection)
    , xcb_gcontext_(xcb_connection_.generate_id())
  {
    // Create a black graphic context for drawing in the foreground
    xcb_drawable_t  window   = xcb_screen->root;
    uint32_t        mask     = XCB_GC_FOREGROUND;
    uint32_t        value[]  = { xcb_screen->black_pixel };

    xcb_create_gc(xcb_connection_, xcb_gcontext_, window, mask, value);

    // FIXME: 'assert(xcb_screen_)'
  }

/*
  The value_mask parameter could take any combination of these masks from
  the xcb_gc_t enumeration:

    XCB_GC_FUNCTION
    XCB_GC_PLANE_MASK
    XCB_GC_FOREGROUND
    XCB_GC_BACKGROUND
    XCB_GC_LINE_WIDTH
    XCB_GC_LINE_STYLE
    XCB_GC_CAP_STYLE
    XCB_GC_JOIN_STYLE
    XCB_GC_FILL_STYLE
    XCB_GC_FILL_RULE
    XCB_GC_TILE
    XCB_GC_STIPPLE
    XCB_GC_TILE_STIPPLE_ORIGIN_X
    XCB_GC_TILE_STIPPLE_ORIGIN_Y
    XCB_GC_FONT
    XCB_GC_SUBWINDOW_MODE
    XCB_GC_GRAPHICS_EXPOSURES
    XCB_GC_CLIP_ORIGIN_X
    XCB_GC_CLIP_ORIGIN_Y
    XCB_GC_CLIP_MASK
    XCB_GC_DASH_OFFSET
    XCB_GC_DASH_LIST
    XCB_GC_ARC_MODE

  It is possible to set several attributes at the same time (for example
  setting the attributes of a font and the color which will be used to
  display a string), by OR'ing these values in value_mask. Then
  value_list has to be an array which lists the value for the respective
  attributes. These values must be in the same order as masks listed
  above.
*/
  xcb_void_cookie_t change(
      uint32_t        value_mask,
      const uint32_t *value_list)
  {
    return xcb_change_gc(xcb_connection_, xcb_gcontext_, value_mask, value_list);
  }
};

} // namespace graphical
} // namespace xcb
