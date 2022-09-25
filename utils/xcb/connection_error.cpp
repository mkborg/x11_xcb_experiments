#include "xcb/connection_error.h"

#include <xcb/xcb.h>

namespace xcb {
namespace connection {
namespace error {

const char * toString(int e)
{
  switch (e) {
    case 0: return "!ERROR";
#define CASE(x) case XCB_CONN_##x: return #x
    // socket errors, pipe errors or other stream errors
    CASE(ERROR);
    // extension not supported
    CASE(CLOSED_EXT_NOTSUPPORTED);
    // memory not available
    CASE(CLOSED_MEM_INSUFFICIENT);
    // exceeding request length that server accepts
    CASE(CLOSED_REQ_LEN_EXCEED);
    // error during parsing display string
    CASE(CLOSED_PARSE_ERR);
    // the server does not have a screen matching the display
    CASE(CLOSED_INVALID_SCREEN);
#undef CASE
    default: return "?";
  }
}

} // namespace error
} // namespace connection
} // namespace xcb
