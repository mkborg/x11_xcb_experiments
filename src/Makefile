.PHONY: all clean default
default: all

CFLAGS += -O2 -Wall -Wextra -MMD
CFLAGS += -I ../utils


SUBDIRS += utils
#SUBDIRS += cxx

include Makefile.SUBDIRS

#xcb_screen_test: .subdir-cxx-all
xcb_screen_test: ${SUBDIRS-ALL}
LIBS += -L utils -lutils
#LIBS += -L cxx -lutils_cxx

LIBS += -lxcb


all: xcb_screen_test
xcb_screen_test: xcb_screen_test.cpp
xcb_screen_test:
	g++ $(CFLAGS) -o xcb_screen_test xcb_screen_test.cpp $(LIBS)

-include xcb_screen_test.d)

clean: clean_xcb_screen_test
.PHONY: clean_xcb_screen_test
clean_xcb_screen_test:
	rm -fv xcb_screen_test
	rm -fv xcb_screen_test.d

all: xcb_window_test
xcb_window_test: xcb_window_test.cpp
xcb_window_test:
	g++ $(CFLAGS) -o xcb_window_test xcb_window_test.cpp $(LIBS)

-include xcb_window_test.d)

clean: clean_xcb_window_test
.PHONY: clean_xcb_window_test
clean_xcb_window_test:
	rm -fv xcb_window_test
	rm -fv xcb_window_test.d
