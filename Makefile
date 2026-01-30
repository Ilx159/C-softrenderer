# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g -I.
LDFLAGS = $(shell sdl2-config --libs) -lm
EXEC = softrenderer

# Source files
SRCS = main.c \
       core/Imath.c \
       engine/renderer.c \
       gfx/framebuffer.c \
       gfx/raster.c \
       gfx/shader.c \
       platform/sdl_window.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJS) $(EXEC)

# Run the executable
run: $(EXEC)
	./$(EXEC)
