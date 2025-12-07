# === Compiler and Flags ===
CXX = g++
CXXFLAGS = -Wall -std=c++11 -MMD -MP
LDLIBS = -lX11 -lpthread

# === Project Structure ===
TARGET = main
TEST_TARGET = test_runner
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build
INCLUDE_DIR = include

# === Auto-generated Paths ===
TARGET_EXEC = $(TARGET)
TEST_EXEC = $(TEST_TARGET)

# Find all source files in src/
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
# All objects from src/
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/src/%.o, $(SOURCES))

# Find all source files in tests/
TEST_SOURCES = $(shell find $(TEST_DIR) -name '*.cpp')
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/tests/%.o, $(TEST_SOURCES))

# Important: We need to separate main.o from the other objects in src
# because main.cpp contains the main() function for the primary app.
# The test runner will have its own main().
MAIN_OBJ = $(BUILD_DIR)/src/main.o
COMMON_OBJS = $(filter-out $(MAIN_OBJ), $(OBJECTS))

# Dependency files
DEPS = $(OBJECTS:%.o=%.d) $(TEST_OBJECTS:%.o=%.d)

CPPFLAGS = -I$(SRC_DIR) -I$(INCLUDE_DIR)

# === Targets ===
all: $(TARGET_EXEC) $(TEST_EXEC)

-include $(DEPS)

# Build the main application
$(TARGET_EXEC): $(COMMON_OBJS) $(MAIN_OBJ)
	@echo "Linking $(TARGET_EXEC)..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Build the test runner
$(TEST_EXEC): $(COMMON_OBJS) $(TEST_OBJECTS)
	@echo "Linking $(TEST_EXEC)..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Compile source files
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Compile test files (add -I$(TEST_DIR) if needed)
$(BUILD_DIR)/tests/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."
	rm -rf $(BUILD_DIR) $(TARGET_EXEC) $(TEST_EXEC)

lint:
	@cpplint --filter=-build/header_guard,-legal/copyright,-whitespace/ending_newline,-whitespace/indent,-whitespace/comments,-runtime/threadsafe_fn,-readability/inheritance,-whitespace/blank_line --recursive src/ include/accessories/ include/sensors/ include/behaviors/ include/core/ include/interfaces/ include/patterns/

actions: clean all lint
	@echo "Actions completed successfully."

.PHONY: all clean lint actions