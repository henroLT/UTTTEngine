CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -pthread
LDFLAGS := -latomic

SRC_DIRS := src headerImpls
OBJ_DIR := bin
TARGET := $(OBJ_DIR)/TTC

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJS := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

INCLUDES := -Iheaders -Iheaders/LFQueue -Iheaders/StateTree

# Default rule: remove and recreate bin, then build
all: clean_bin $(TARGET)

# Create target from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

# Compile rule for src
$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile rule for headerImpls
$(OBJ_DIR)/%.o: headerImpls/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Recreate bin/ directory every time
clean_bin:
	rm -rf $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)

# Clean object files and target
clean:
	rm -rf $(OBJ_DIR)
