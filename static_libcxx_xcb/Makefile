.PHONY: all clean default
default: all

# Let's use '.SECONDEXPANSION:' for substitutions in prerequisites
.SECONDEXPANSION:

LIBDIR := LIBDIR

LIB_NAME := xcb
LIB_FILE := $(LIBDIR)/libcxx_$(LIB_NAME).a
$(info "LIB_FILE='$(LIB_FILE)'")

SOURCES += $(wildcard src/$(LIB_NAME)/*.c)
SOURCES += $(wildcard src/$(LIB_NAME)/*.cpp)
$(info "SOURCES='$(SOURCES)'")

OBJDIR := OBJDIR
OBJECTS := $(patsubst %,$(OBJDIR)/%.o,$(SOURCES))
$(info "OBJECTS='$(OBJECTS)'")
OBJECTS_DIRS := $(sort $(dir $(OBJECTS)))
$(info "OBJECTS_DIRS='$(OBJECTS_DIRS)'")

ARFLAGS = crv

CFLAGS += -I include
CFLAGS += -I ../utils

CFLAGS += -O2
CFLAGS += -fvisibility=hidden
CFLAGS += -MMD
CFLAGS += -Wall
CFLAGS += -Wextra

CC := gcc
CXX := g++

-include $(OBJECTS:.o=.d)

$(OBJDIR)/%.c.o : %.c | $$(dir $$@)
	$(CC) -c $(CFLAGS) -o $@ $<

# C++ sources compilation
$(OBJDIR)/%.cpp.o: %.cpp | $$(dir $$@)
	$(CXX) -c $(CXXFLAGS) $(CFLAGS) -o $@ $<

all: $(LIB_FILE)
$(LIB_FILE): $(OBJECTS)
$(LIB_FILE): $$(dir $$@)
$(LIB_FILE):
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
#	$(AR) $(ARFLAGS) $@ $^

# Directories for object files and binaries
BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS) $(dir $(LIB_FILE)))
#BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS))
$(info BUILD_SUBDIRS="$(BUILD_SUBDIRS)")
$(BUILD_SUBDIRS):
	mkdir -pv $@

.PHONY: clean_$(LIB_FILE)
clean: clean_$(LIB_FILE)
clean_$(LIB_FILE):
	rm -fv $(LIB_FILE)
	rm -fv $(OBJECTS)
	rm -fv $(OBJECTS:.o=.d)
	-rmdir -pv $(BUILD_SUBDIRS)
	rm -rfv $(OBJDIR)
