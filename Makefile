# all: main.cpp
# 	g++ -o photosynthesis src/glad.c main.cpp -Iinclude -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl 
# 	./photosynthesis
CC :=gcc
CXX :=g++
LDFLAGS := -Iinclude -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-4 -pthread -lfreetype 
CSOURCES :=$(wildcard src/*.c)
CXXSOURCES :=$(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
EXECUTABLE :=photosynthesis
 
all:clean photosynthesis

photosynthesis:
	$(CXX) -o ./$(EXECUTABLE) main.cpp $(CXXSOURCES) $(CSOURCES) $(LDFLAGS)
	./$(EXECUTABLE)

asteroids: clean
	$(CXX) -o ./asteroids asteroids.cpp $(CXXSOURCES) $(CSOURCES) $(LDFLAGS)
	./asteroids
debug:
	$(CXX) -o ./$(EXECUTABLE) main.cpp $(CXXSOURCES) $(CSOURCES) $(LDFLAGS) -g
	./$(EXECUTABLE)
clean:
		rm -rf $(EXECUTABLE) asteroids