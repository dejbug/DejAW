include common.mk

PRECISE := 1
DEBUG := 0

NAME := DejAW
TARGET := console
SOURCE_ROOT := src

INCDIRS := $(SOURCE_ROOT)
SYMBOLS := WIN32_LEAN_AND_MEAN STRICT
WINLIBS := gdi32

CXXFLAGS := --std=c++17 -Wall -Wextra -pedantic-errors
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += -fmax-errors=1
CXXFLAGS += -fdiagnostics-color=always
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

SOURCES := main app lib
SOURCES := $(SOURCES:%=$(SOURCE_ROOT)/%)
SOURCES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
PREREQS := $(SOURCES:src/%.cpp=build/%.d)
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)
SUBDIRS := $(call DISTINCT,$(dir $(OBJECTS)))

deploy/$(NAME).exe : build/$(NAME).exe | deploy
	$(call COPY,$<,$@)
	$(call MINIMIZE,$@)

build/$(NAME).exe : build/resource.o
build/$(NAME).exe : $(OBJECTS) | build ; $(call LINK,$@,$^)

deploy build $(SUBDIRS) : ; $(call MAKETREE,$@)

build/%.o : src/%.cpp | build $(SUBDIRS) ; $(call COMPILE,$@,$^)
build/%.d : src/%.cpp | build $(SUBDIRS) ; $(call GENREQS,$@,$<)

build/resource.o: src/main/main.rc | $(SUBDIRS) ; windres $< $@

clean : ; $(call DELTREE,build)
reset : | clean ; $(call DELTREE,deploy)
run : build/$(NAME).exe ; $(call W,@.\$<)

ifneq ($(PRECISE),0)
ifeq (,$(call HAS_NON_BUILD_GOAL))
include $(PREREQS)
endif
endif

.PHONY : clean reset run
.DELETE_ON_ERROR :
