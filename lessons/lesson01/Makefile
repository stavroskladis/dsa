# Simple Makefile for Lesson 1: Getting Started
# Compiles all .cpp files in this directory

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

# Find all .cpp files in current directory
SOURCES = $(wildcard *.cpp)
TARGETS = $(SOURCES:.cpp=)

# Default target
all: $(TARGETS)

# Compile each .cpp file to executable
%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean target - remove all executables
clean:
	rm -f $(TARGETS)

# Show help
help:
	@echo "Available targets:"
	@echo "  all    - Compile all .cpp files"
	@echo "  clean  - Remove all executables"
	@echo "  help   - Show this help message"
	@echo ""
	@echo "To compile a specific file: make filename"
	@echo "To run a program: ./filename"
