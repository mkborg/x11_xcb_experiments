.PHONY: all clean default
default: all

# Let's use '.SECONDEXPANSION:' for substitutions in prerequisites
.SECONDEXPANSION:

#LIB_NAME := utils_cxx
LIB_NAME := utils
LIB_FILE := lib$(LIB_NAME).a
$(info "LIB_FILE='$(LIB_FILE)'")

SOURCES += $(wildcard src/cxx/*.c)
SOURCES += $(wildcard src/cxx/*.cpp)
$(info "SOURCES='$(SOURCES)'")

OBJDIR := OBJDIR
OBJECTS := $(patsubst %,$(OBJDIR)/%.o,$(SOURCES))
$(info "OBJECTS='$(OBJECTS)'")
OBJECTS_DIRS := $(sort $(dir $(OBJECTS)))
$(info "OBJECTS_DIRS='$(OBJECTS_DIRS)'")

ARFLAGS = crv

CFLAGS += -I include
CFLAGS += -O2
CFLAGS += -fvisibility=hidden
CFLAGS += -MMD
CFLAGS += -Wall
CFLAGS += -Wextra

CC := gcc
CXX := g++

$(OBJDIR)/%.c.o : %.c | $(DEPENDENCIES) $$(dir $$@)
	$(CC) -c $(CFLAGS) -o $@ $<

# C++ sources compilation
$(OBJDIR)/%.cpp.o: %.cpp | $(DEPENDENCIES) $$(dir $$@)
	$(CXX) -c $(CXXFLAGS) $(CFLAGS) -o $@ $<

all: $(LIB_FILE)
$(LIB_FILE): $(OBJECTS)
$(LIB_FILE):
	$(AR) $(ARFLAGS) $@ $^

# Directories for object files and binaries
#BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS) $(dir $(LIB_FILE)))
BUILD_SUBDIRS := $(sort $(OBJECTS_DIRS))
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
