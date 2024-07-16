# Define the compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Define the target executables
TARGET = demo
TEST_TARGET = tests

# Define the source files and object files for the main program
SRCS = Demo.cpp tree.cpp node.cpp
OBJS = $(SRCS:.cpp=.o)

# Define the source files and object files for the tests
TEST_SRCS = TestCounter.cpp Test.cpp tree.cpp node.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# Default target to build the project
all: $(TARGET) $(TEST_TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to build the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Rule to build object files from source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean the build directory
clean:
	rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

# Rule to run the target executable
run: $(TARGET)
	./$(TARGET)

# Rule to run the tests
run-tests: $(TEST_TARGET)
	./$(TEST_TARGET)
