CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror
LDFLAGS = -lpthread

SRCS = http_server.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = http_server

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
