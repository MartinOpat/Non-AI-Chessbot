# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall

# Source files
SRCS = bot.cpp endgames.cpp eval.cpp movegen.cpp openings.cpp utils.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable
TARGET = chessbot

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile source files
.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)
