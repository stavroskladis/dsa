# Root Makefile for C++ Learning Project
# Compiles all lessons or specific lessons

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra

# Get all lesson directories
LESSONS = $(wildcard lessons/lesson*)

# Default target - compile all lessons
all: $(LESSONS)

# Compile each lesson
$(LESSONS):
	@echo "Compiling $@..."
	@$(MAKE) -C $@

# Clean all lessons
clean:
	@echo "Cleaning all lessons..."
	@for lesson in $(LESSONS); do \
		$(MAKE) -C $$lesson clean; \
	done

# Show available targets
help:
	@echo "Available targets:"
	@echo "  all    - Compile all lessons"
	@echo "  clean  - Clean all lessons"
	@echo "  help   - Show this help message"
	@echo ""
	@echo "To compile a specific lesson: make lessons/lesson01-Sorting"
	@echo "To clean a specific lesson: make -C lessons/lesson01-Sorting clean"

# Show lesson list
lessons:
	@echo "Available lessons:"
	@for lesson in $(LESSONS); do \
		echo "  $$lesson"; \
	done

.PHONY: all clean help lessons $(LESSONS)
