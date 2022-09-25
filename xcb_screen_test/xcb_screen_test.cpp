#include "xcb/connection.h"
#include "xcb/screen.h"
#include "xcb/screen_iterator.h"
#include "xcb/setup.h"

#include <stdio.h>

void report_xcb_screen(const xcb::screen::Iterator& xcb_screen_iterator)
{
  printf("(bool)xcb_screen_iterator=%i\n", (bool)xcb_screen_iterator);
  const auto xcb_screen = xcb::Screen(xcb_screen_iterator);
  printf("xcb_screen='%s'\n", xcb_screen.toString().c_str());
  printf("in_pixels=%ux%u\n", xcb_screen.width_in_pixels(), xcb_screen.height_in_pixels());
  printf("in_millimeters=%ux%u\n", xcb_screen.width_in_millimeters(), xcb_screen.height_in_millimeters());
}

int main()
{
  auto xcb_connection = xcb::Connection();
  auto xcb_setup = xcb::Setup(xcb_connection);
  auto xcb_screen_iterator = xcb::screen::Iterator(xcb_setup);
  //printf("xcb_connection.screen()=%i\n", xcb_connection.screen());

  // Note: according to the 'xcb tutorial' some 'iteration' is necessary
  // if 'xcb_connection.screen()' is non-zero.
#if 1
  const auto screen = xcb_connection.screen();
#else
  int screen = 3;
#endif
  for (int i = 0; i < screen; ++i) {
    printf("i=%i\n", i);
    report_xcb_screen(xcb_screen_iterator);
    ++xcb_screen_iterator;
  }

  report_xcb_screen(xcb_screen_iterator);

  ++xcb_screen_iterator;
  report_xcb_screen(xcb_screen_iterator);

  return 0;
}
