# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g -fPIC  # Add -fPIC here for position-independent code

# Source files
SRCS = bot.cpp endgames.cpp eval.cpp movegen.cpp openings.cpp utils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Shared library target
TARGET_LIB = chessbot4.so  # Change this to your shared library name

# Executable target
TARGET_EXE = bot.out

# Build shared library
$(TARGET_LIB): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(TARGET_LIB) $(OBJS)

# Build executable
$(TARGET_EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET_EXE) $(OBJS)

# Compile source files
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET_LIB) $(TARGET_EXE)

# Phony targets for make commands
.PHONY: clean exe

# Command to make executable
exe: $(TARGET_EXE)
