CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./Elevate
LDFLAGS = -lSDL2 -lSDL2_mixer -ltag

SRCS = main.cpp \
       IController.cpp \
       File.cpp

OBJS = $(SRCS:.cpp=.o)

TARGET = MediaPlayer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
