include common.mk

PRECISE := 1
DEBUG := 1

NAME := DejAW
TARGET := console
SOURCE_ROOT := src

INCDIRS := src
SYMBOLS := WIN32_LEAN_AND_MEAN STRICT
WINLIBS := gdi32

CXXFLAGS := --std=c++11 -fabi-version=11 -Wall -Wpedantic
CXXFLAGS +=	$(addprefix -I,$(INCDIRS))
CXXFLAGS +=	$(addprefix -D,$(SYMBOLS))

LDFLAGS :=
ifeq ($(TARGET),windows)
LDFLAGS += -Wl,--subsystem=windows
DEBUG := 0
else
LDFLAGS += -Wl,--subsystem=console
endif

ifneq ($(DEBUG),0)
CXXFLAGS += -g -Og
else
CXXFLAGS += -O3 -DNDEBUG
endif

LDLIBS := $(addprefix -l,$(WINLIBS))

SOURCES := $(call LIST_DIR,$(SOURCE_ROOT))
SOURCES := $(filter %.cpp,$(SOURCES))
PREREQS := $(SOURCES:src/%.cpp=build/%.d)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)
SUBDIRS := $(call DISTINCT,$(dir $(OBJECTS)))

$(info SOURCES $(SOURCES))
$(info SUBDIRS $(SUBDIRS))

deploy/$(NAME).exe : build/resource.o
deploy/$(NAME).exe : $(OBJECTS) | deploy/ ; $(call LINK,$@,$^)

deploy/ build/ : ; $(call MAKE_DIR,$(call STRIP_PATH,$@))
$(SUBDIRS) : ; $(call MAKE_DIR,$@)

build/%.o : src/%.cpp | $(SUBDIRS) ; $(call COMPILE,$@,$^)
build/%.d : src/%.cpp | $(SUBDIRS) ; $(call GEN_PREREQ,$@,$<)

build/resource.o: src/main/main.rc | $(SUBDIRS) ; windres $< $@

.PHONY : clean reset run

clean : ; $(call REMOVE_TREE,build/)
reset : | clean ; $(call REMOVE_TREE,deploy/)
run : deploy/$(NAME).exe ; $<

ifneq ($(PRECISE),0)
ifeq (,$(call HAS_NON_BUILD_GOAL))
include $(PREREQS)
endif
endif

.DELETE_ON_ERROR :
