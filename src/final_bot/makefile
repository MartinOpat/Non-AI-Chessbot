# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g -fPIC  # Add -fPIC here for position-independent code

# Source files
SRCS = bot.cpp endgames.cpp eval.cpp movegen.cpp openings.cpp utils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Shared library target
TARGET = chessbot4.so  # Change this to your shared library name

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(TARGET) $(OBJS)  # Add -shared flag here

# Compile source files
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)  # Removes the shared library as well; adjust if necessary
