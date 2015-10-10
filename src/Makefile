####################
#
# Linux Makefile
#
####################


#
# Object Files
#

OBJS = $(patsubst %.c,%.o,$(wildcard *.c))


#
# Project Info
#

PROJ = xcom


#
# Compiler Info
#

# clang
CC = gcc

# includes

INC_PATHS = ../include
INC_PARAMS = $(foreach d, $(INC_PATHS), -I$d)

# compiler flags
GLIB_CFLAGS = `pkg-config --cflags glib-2.0`
GLIB_LDFLAGS = `pkg-config --libs glib-2.0`

SDL_CFLAGS = `sdl2-config --cflags`
SDL_LDFLAGS = `sdl2-config --libs` -lm -lSDL2_image -lpng -ljpeg -lz -lGL -lGLEW -lGLU -lyaml

LFLAGS = -g -o $(PROJ)
CFLAGS = -g $(INC_PARAMS) -Wall -pedantic -std=gnu99 -fgnu89-inline -Wno-unknown-pragmas -Wno-variadic-macros


#
# Compiling
#

$(PROJ): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(SDL_LDFLAGS) $(GLIB_LDFLAGS) 


#
# Directory Cleanup
#

clean:
	rm *.o ../$(PROJ)
	
	
#
# Documentation Creation
#

DOXYGEN = doxygen

docs:
	$(DOXYGEN) doxygen.cfg

	
#
# Dependency Creation
#

makefile.dep: depend

depend:
	@touch makefile.dep
	@-rm makefile.dep
	@echo Creating dependencies.
	@for i in *.c; do $(CC) $(INC) $(INC_PARAMS) -MM $$i; done > makefile.dep
	@echo Done.
	
include makefile.dep


#
# The default rule.
#

.c.o:
	$(CC) $(CFLAGS) $(SDL_CFLAGS) $(GLIB_CFLAGS) -c $<
