# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Compiler / linker
CC = cl
CFLAGS = /Zi /Od
LDFLAGS = gdi32.lib user32.lib

# Target
TARGET = main

# Sources and objects
SRCS = \
	me_entry.c \
	me_paint.c \
	me_structure_blueprint.c \
	basic_stuff.c

equation-display-example:
	cl main.c $(SRCS) $(LDFLAGS) /Zi /Od

clean:
	del *.exe
	del *.ilk
	del *.obj
	del *.pdb
	