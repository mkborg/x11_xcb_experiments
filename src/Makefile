.PHONY: all clean default
default: all

all: xcb_screen_test
xcb_screen_test: xcb_screen_test.cpp
xcb_screen_test:
	g++ -O2 -Wall -Wextra -MMD -o xcb_screen_test xcb_screen_test.cpp -lxcb

-include xcb_screen_test.d)

clean: clean_xcb_screen_test
.PHONY: clean_xcb_screen_test
clean_xcb_screen_test:
	rm -fv xcb_screen_test