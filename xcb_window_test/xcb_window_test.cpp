#include "xcb/connection.h"
#include "xcb/screen.h"
#include "xcb/screen_iterator.h"
#include "xcb/setup.h"
#include "xcb/window.h"

//#include <stdio.h>
#include <unistd.h>      // pause()

int main()
{
  auto xcb_connection = xcb::Connection();
  auto xcb_setup = xcb::Setup(xcb_connection);
  auto xcb_screen_iterator = xcb::screen::Iterator(xcb_setup);

  // Note: according to the 'xcb tutorial' some 'iteration' is necessary
  // if 'xcb_connection.screen()' is non-zero.
  const auto screen = xcb_connection.screen();
  for (int i = 0; i < screen; ++i) {
    ++xcb_screen_iterator;
  }

  auto xcb_screen = xcb::Screen(xcb_screen_iterator);
  auto xcb_window = xcb::Window(xcb_connection, xcb_screen);
  xcb_window.show();
  xcb_connection.flush();

  /*
    The pause() function shall suspend the calling thread until delivery
    of a signal whose action is either to execute a signal-catching
    function or to terminate the process.
  */
  pause();

  return 0;
}
