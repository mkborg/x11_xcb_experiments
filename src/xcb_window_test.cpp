#include "xcb_connection.h"
#include "xcb_screen.h"
#include "xcb_screen_iterator.h"
#include "xcb_setup.h"
#include "xcb_window.h"

//#include <stdio.h>
#include <unistd.h>      // pause()

int main()
{
  auto xcb_connection = xcb::Connection();
  auto xcb_setup = xcb::Setup(xcb_connection);
  auto xcb_screen_iterator = xcb::screen::Iterator(xcb_setup);
  auto xcb_screen = xcb::Screen(xcb_screen_iterator);
  auto xcb_window = xcb::Window(xcb_connection, xcb_screen);
  xcb_window.show();
  xcb_connection.flush();

  pause();

  return 0;
}
