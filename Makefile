CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC = $(shell find src -name '*.cpp')
OBJ = $(SRC:.cpp=.o)
TARGET = build/os_simulator

all: $(TARGET)

$(TARGET): $(OBJ) main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ) main.cpp

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)
