CXX = gcc
CFLAGS = #-Wall -Wextra -Werror
COMPILER_CALL = $(CXX) # $(CFLAGS)
LDFLAGS = -lraylib

CSOURCES = $(wildcard *.c)
COBJS = $(patsubst %.c, %.o, $(CSOURCES))

APP_NAME = todo

# all: todo

all: $(COBJS)
	$(COMPILER_CALL) -o main main.o collisionManager.o $(LDFLAGS)

%.o: %.c
	$(COMPILER_CALL) -c $< -o $@

clean:
	rm -f $(COBJS)