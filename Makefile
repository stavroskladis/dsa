# Root Makefile for C++ Learning Project
# Compiles all topics or specific topics

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra

# Get all topic directories
TOPICS = $(wildcard topics/*)

# Default target - compile all topics
all: $(TOPICS)

# Compile each topic
$(TOPICS):
	@echo "Compiling $@..."
	@$(MAKE) -C $@

# Clean all topics
clean:
	@echo "Cleaning all topics..."
	@for topic in $(TOPICS); do \
		$(MAKE) -C $$topic clean; \
	done

# Show available targets
help:
	@echo "Available targets:"
	@echo "  all    - Compile all topics"
	@echo "  clean  - Clean all topics"
	@echo "  help   - Show this help message"
	@echo ""
	@echo "To compile a specific topic: make topics/01-Sorting"
	@echo "To clean a specific topic: make -C topics/01-Sorting clean"

# Show topic list
topics:
	@echo "Available topics:"
	@for topic in $(TOPICS); do \
		echo "  $$topic"; \
	done

.PHONY: all clean help topics $(TOPICS)
