#pragma once

#include "xcb/screen_iterator.h"

#include <xcb/xcb.h>

#include <string>

#include <sstream>

namespace xcb {

/*
    typedef struct {
        xcb_window_t   root;
        xcb_colormap_t default_colormap;
        uint32_t       white_pixel;
        uint32_t       black_pixel;
        uint32_t       current_input_masks;
        uint16_t       width_in_pixels;
        uint16_t       height_in_pixels;
        uint16_t       width_in_millimeters;
        uint16_t       height_in_millimeters;
        uint16_t       min_installed_maps;
        uint16_t       max_installed_maps;
        xcb_visualid_t root_visual;
        uint8_t        backing_stores;
        uint8_t        save_unders;
        uint8_t        root_depth;
        uint8_t        allowed_depths_len;
    } xcb_screen_t;
*/

class Screen
{
private:
  const xcb_screen_t * xcb_screen_;

public:
  xcb_screen_t const * operator ->() const
  {
    return xcb_screen_;
  }

  ~Screen()
  {
/*
    if (xcb_connection_) {
      xcb_disconnect(xcb_connection_);
    }
*/
  }

  Screen(const xcb_screen_iterator_t xcb_screen_iterator)
    : xcb_screen_(xcb_screen_iterator.data)
  {
    // FIXME: 'assert(xcb_screen_)'
  }

  Screen(const xcb::screen::Iterator& xcb_screen_iterator)
    : xcb_screen_(xcb_screen_iterator.screen())
  {
    // FIXME: 'assert(xcb_screen_)'
  }

  inline uint16_t width_in_pixels() const { return xcb_screen_->width_in_pixels; }
  inline uint16_t height_in_pixels() const { return xcb_screen_->height_in_pixels; }
  inline uint16_t width_in_millimeters() const { return xcb_screen_->width_in_millimeters; }
  inline uint16_t height_in_millimeters() const { return xcb_screen_->height_in_millimeters; }

  std::string toString() const
  {
    std::ostringstream oss;

    oss << "width_in_pixels=" << xcb_screen_->width_in_pixels;
    oss << " height_in_pixels=" << xcb_screen_->height_in_pixels;

    return oss.str();
  }
};

} // namespace xcb
