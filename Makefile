CFLAGS = -O3 -funroll-loops -g -Wall -ansi
#CFLAGS = -O1 -g -Wall -ansi
#CFLAGS = -g -Wall -ansi
CC = g++
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
PROG = Reversi

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	PROG = Reversi.exe
endif

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm $(OBJS) $(PROG)
