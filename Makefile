# === Compiler and Flags ===
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDLIBS = -lX11 -lpthread

# === Project Structure ===
# Executable name
TARGET = main

# Directories
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include # For 3rd-party headers like CImg.h

# === Auto-generated Paths ===
# Full path to the final executable
TARGET_EXEC = $(BUILD_DIR)/$(TARGET)

# Find all .cpp files in the source directory
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Create a list of corresponding .o files in the build directory
# e.g., src/Bestiole.cpp -> build/Bestiole.o
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# Include paths for the preprocessor (-I)
# Tells g++ to look for headers in src/ and include/
CPPFLAGS = -I$(SRC_DIR) -I$(INCLUDE_DIR)

# === Targets ===

# The default target (what runs when you just type 'make')
all: $(TARGET_EXEC)

# Rule to link the final executable
# Depends on all .o files
$(TARGET_EXEC): $(OBJECTS)
	@mkdir -p $(BUILD_DIR) # Ensure build dir exists
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Pattern rule to compile .cpp files into .o files
# $(BUILD_DIR)/%.o: This is the target (e.g., build/main.o)
# $(SRC_DIR)/%.cpp: This is the prerequisite (e.g., src/main.cpp)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR) # Ensure build dir exists
	@echo "Compiling $<..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Rule to clean up all build files
clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR)

# Declare 'all' and 'clean' as phony targets
# This tells 'make' that they aren't actual files
.PHONY: all clean