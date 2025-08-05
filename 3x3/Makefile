CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -O2 -pthread

SRCS := src/runner.cpp headerImpls/solver.cpp headerImpls/lfqueue.cpp
OBJS := $(SRCS:.cpp=.o)
TARGET := bin/TTC

all: $(TARGET)

$(TARGET): &(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)