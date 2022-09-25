.PHONY: all clean default
default: all

CFLAGS += -O2 -Wall -Wextra -MMD

CFLAGS += -I ../static_libcxx/include
CFLAGS += -I ../static_libcxx_xcb/include
CFLAGS += -I ../static_libutils/include

LIBS += -L ../static_libcxx_xcb/LIBDIR -lcxx_xcb
LIBS += -L ../static_libcxx/LIBDIR     -lcxx
LIBS += -L ../static_libutils/LIBDIR   -lutils

LIBS += -lxcb

all: xcb_window_test
xcb_window_test: xcb_window_test.cpp
xcb_window_test:
	g++ $(CFLAGS) -o xcb_window_test xcb_window_test.cpp $(LIBS)

-include xcb_window_test.d

clean: clean_xcb_window_test
.PHONY: clean_xcb_window_test
clean_xcb_window_test:
	rm -fv xcb_window_test
	rm -fv xcb_window_test.d
