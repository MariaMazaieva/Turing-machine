# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g

# Target executable
TARGET = t_machine

# For deleting the target
TARGET_DEL = t_machine.o

# Source files
SRCS = t_machine.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET) run

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to run the executable
run: $(TARGET)
	./$(TARGET) < test.txt

# Clean rule to remove generated files
clean:
	rm -f $(TARGET_DEL) $(OBJS)

