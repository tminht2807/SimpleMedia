# Compiler
CXX = g++
CXXFLAGS = -Wall -std=c++17

# SDL and TagLib Include and Library Paths (modify as needed)
INCLUDES = -I/usr/include/SDL2
LIBS = -lSDL2 -lSDL2_mixer -ltag

# Source Files
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

# Output Executable
TARGET = simple_media_player

# Build Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)