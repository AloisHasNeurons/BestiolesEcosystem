# === Compiler and Flags ===
CXX = g++
CXXFLAGS = -Wall -std=c++11 -MMD -MP
LDLIBS = -lX11 -lpthread

# === Project Structure ===
TARGET = main
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# === Auto-generated Paths ===
TARGET_EXEC = $(TARGET)
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SOURCES))

# It creates a list of dependency files (e.g., build/main.d, build/Bestiole.d)
# that will correspond to our object files.
DEPS = $(OBJECTS:%.o=%.d)

CPPFLAGS = -I$(SRC_DIR) -I$(INCLUDE_DIR)

# === Targets ===
all: $(TARGET_EXEC)

-include $(DEPS)

$(TARGET_EXEC): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning..."	rm -rf $(BUILD_DIR) $(TARGET_EXEC)
	rm -rf $(BUILD_DIR) $(TARGET_EXEC)

lint:
	@cpplint --filter=-build/header_guard,-legal/copyright,-whitespace/ending_newline,-whitespace/indent,-whitespace/comments,-runtime/threadsafe_fn,-readability/inheritance,-whitespace/blank_line --recursive src/ include/accessories/ include/sensors/ include/behaviors/ include/core/ include/interfaces/ include/patterns/

actions: clean all lint
	@echo "Actions completed successfully."

.PHONY: all clean lint actions