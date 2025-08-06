CXX := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -pthread
LDFLAGS := -latomic

SRC_DIRS := src headers/headerImpls
OBJ_DIR := bin
TARGET := $(OBJ_DIR)/TTC

SRCS := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRCS))

INCLUDES := -Iheaders -Iheaders/LFQueue -Iheaders/StateTree

.PHONY: default log help clean clean_bin

default: clean_bin $(TARGET)
	@echo "\033[1;4mMake successful - wait 2 seconds.\033[0m"
	@sleep 2
	@clear

log: clean_bin $(TARGET)

help:
	@echo "\"make\" for general purpose build."
	@echo "\"make log\" to make with logs kept."
	@echo "\"make clean\" to clean."

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean_bin:
	rm -rf $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
