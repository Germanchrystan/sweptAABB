CXX ?= g++
CXXWARNINGS = -Wall -Wextra -Werror
CXXFLAGS ?= -std=c++17 # $(CXXWARNINGS)

PKG_CONFIG ?= pkg-config
RAYLIB_CFLAGS := $(shell $(PKG_CONFIG) --cflags raylib)
RAYLIB_LIBS   := $(shell $(PKG_CONFIG) --libs raylib)

CSOURCES = $(wildcard *.cpp) # Get all .cpp files in the current directory
COBJS = $(patsubst %.cpp, %.o, $(CSOURCES))

all: mario

mario: $(COBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(COBJS) $(RAYLIB_LIBS)
	rm -f $(COBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) -c $< -o $@

clean:
	rm -f $(COBJS)

run:
	./rectangles