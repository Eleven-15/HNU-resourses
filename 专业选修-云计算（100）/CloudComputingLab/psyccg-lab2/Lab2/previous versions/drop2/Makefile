CC := g++
CFLAGS := -Wall -Wextra -std=c++11
LDFLAGS := -pthread

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
EXECUTABLE := http-server

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXECUTABLE)
