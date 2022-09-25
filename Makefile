.PHONY: all clean default
default: all

SUBDIRS += xcb_screen_test
SUBDIRS += xcb_window_test

.PHONY: LIBSUBDIRS
LIBSUBDIRS += static_libcxx
LIBSUBDIRS += static_libcxx_xcb
LIBSUBDIRS += static_libutils
SUBDIRS += $(LIBSUBDIRS)

include Makefile.SUBDIRS

.PHONY: LIBSUBDIRS-ALL
LIBSUBDIRS-ALL += .subdir-static_libcxx-all
LIBSUBDIRS-ALL += .subdir-static_libcxx_xcb-all
LIBSUBDIRS-ALL += .subdir-static_libutils-all

.subdir-xcb_screen_test-all: $(LIBSUBDIRS-ALL)
.subdir-xcb_window_test-all: $(LIBSUBDIRS-ALL)
