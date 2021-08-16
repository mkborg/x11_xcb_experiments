#include "xcb_connection.h"
#include "xcb_screen.h"
#include "xcb_screen_iterator.h"
#include "xcb_setup.h"

#include <stdio.h>

int main()
{
  auto xcb_connection = xcb::Connection();
  auto xcb_setup = xcb::Setup(xcb_connection);
  auto xcb_screen_iterator = xcb::screen::Iterator(xcb_setup);
  auto xcb_screen = xcb::Screen(xcb_screen_iterator);

  printf("xcb_connection.screen()=%i\n", xcb_connection.screen());
  printf("(bool)xcb_screen_iterator=%i\n", (bool)xcb_screen_iterator);
  printf("xcb_screen='%s'\n", xcb_screen.toString().c_str());
  printf("in_pixels=%ux%u\n", xcb_screen.width_in_pixels(), xcb_screen.height_in_pixels());
  printf("in_millimeters=%ux%u\n", xcb_screen.width_in_millimeters(), xcb_screen.height_in_millimeters());
  ++xcb_screen_iterator;
  printf("(bool)xcb_screen_iterator=%i\n", (bool)xcb_screen_iterator);

  return 0;
}
