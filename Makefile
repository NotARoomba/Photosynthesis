# all: main.cpp
# 	g++ -o photosynthesis src/glad.c main.cpp -Iinclude -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl 
# 	./photosynthesis
CC :=gcc
CXX :=g++
LDFLAGS := -Iinclude -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl 
CSOURCES :=$(wildcard src/*.c)
CXXSOURCES :=$(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
EXECUTABLE :=photosynthesis
 
all:clean photosynthesis

photosynthesis:
	$(CXX) -o ./$(EXECUTABLE) $(CXXSOURCES) $(CSOURCES) $(LDFLAGS)
	./$(EXECUTABLE)


clean:
		rm -rf $(EXECUTABLE)