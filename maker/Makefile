#
# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X
#
# You will need SDL2 (http://www.libsdl.org):
# Linux:
#   apt-get install libsdl2-dev
# Mac OS X:
#   brew install sdl2
# MSYS2:
#   pacman -S mingw-w64-i686-SDL
#

#CXX = g++
#CXX = clang++
EXEDIR = ..
EXE = gui_test_proto
SOURCES = gui_main.cpp
SOURCES += ../src/gui-fe/wrappers/imgui_impl_sdl.cpp ../src/gui-fe/wrappers/imgui_impl_opengl3.cpp
SOURCES += ../src/imgui-master/imgui.cpp ../src/imgui-master/imgui_demo.cpp ../src/imgui-master/imgui_draw.cpp ../src/imgui-master/imgui_widgets.cpp
OBJDIR = ../obs
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
UNAME_S := $(shell uname -s)

CXXFLAGS = -I../src/gui-fe/wrappers/ -I../src/imgui-master/
CXXFLAGS += -g -Wall -Wformat
LIBS =

##---------------------------------------------------------------------
## OPENGL LOADER
##---------------------------------------------------------------------

## Using OpenGL loader: gl3w [default]
SOURCES += ../src/gui-fe/libs/gl3w/GL/gl3w.c
CXXFLAGS += -I../src/gui-fe/libs/gl3w -DIMGUI_IMPL_OPENGL_LOADER_GL3W

##---------------------------------------------------------------------
## BUILD FLAGS PER PLATFORM
##---------------------------------------------------------------------
ifeq ($(UNAME_S), Linux)
	ECHO_MESSAGE = "Linux"
	LIBS += -lGL -ldl `sdl2-config --libs`

	CXXFLAGS += `sdl2-config --cflags`
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(UNAME_S), Darwin) #APPLE
	ECHO_MESSAGE = "Mac OS X"
	LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo `sdl2-config --libs`
	LIBS += -L/usr/local/lib -L/opt/local/lib

	CXXFLAGS += `sdl2-config --cflags`
	CXXFLAGS += -I/usr/local/include -I/opt/local/include
	CFLAGS = $(CXXFLAGS)
endif

ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
   ECHO_MESSAGE = "MinGW"
   LIBS += -lgdi32 -lopengl32 -limm32 `pkg-config --static --libs sdl2`

   CXXFLAGS += `pkg-config --cflags sdl2`
   CFLAGS = $(CXXFLAGS)
endif
##---------------------------------------------------------------------
## BUILD RULES
##---------------------------------------------------------------------

$(OBJDIR)/%.o:../src/gui-fe/%.cpp
	$(CXX) $(CXXFLAGS) --std=c++17 -c -o $@ $<

$(OBJDIR)/%.o:../src/gui-fe/wrappers/%.cpp
	$(CXX) $(CXXFLAGS) --std=c++17 -c -o $@ $<

$(OBJDIR)/%.o:../src/gui-fe/libs/gl3w/GL/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

#%.o:src/logic-be/%.cpp
#	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:../src/imgui-master/%.cpp
	$(CXX) $(CXXFLAGS) --std=c++17 -c -o $@ $<

all: $(EXEDIR)/$(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXEDIR)/$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXEDIR)/$(EXE) $(OBJS)
