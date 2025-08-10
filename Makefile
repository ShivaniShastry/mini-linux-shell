CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRC = main.cpp prompt.cpp piping.cpp tokeniser.cpp shell.cpp builtins.cpp
OBJ = $(SRC:.cpp=.o)

TARGET = shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
