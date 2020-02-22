W = $(subst /,\,$1)

DISTINCT = $(sort $1)

HAS_GOAL = $(findstring $1,$(MAKECMDGOALS))
HAS_GOALS = $(or $(foreach goal,$1,$(findstring $(goal),$(MAKECMDGOALS))))

LINK_F = $(filter %.o %.a %.dll,$1)
LINK = $(CXX) -o $1 $(call LINK_F,$2) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

COMPILE_F = $(filter %.cpp %.c %.cxx,$1)
COMPILE = $(CXX) -o $1 -c  $(call COMPILE_F,$2) $(CXXFLAGS)

GENREQS = $(CXX) -MF $1 -MM -MG $2 -MT "$1 $(1:.d=.o)" $(CXXFLAGS)

HAS_NON_BUILD_GOAL = $(call HAS_GOALS,clean reset)

MAKETREE_ = IF NOT EXIST $1 MKDIR $1
MAKETREE = $(call MAKETREE_,$(call W,$1))

DELTREE_ = IF EXIST $1 RMDIR /S /Q $1
DELTREE = $(call DELTREE_,$(call W,$1))

COPY = COPY /Y $(call W,$1 $2) 1>NUL

MINIMIZE = strip $1 && upx -9 $1
