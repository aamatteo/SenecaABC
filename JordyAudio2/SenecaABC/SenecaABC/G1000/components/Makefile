#TARGET  = components.o
CODEGEN = ifparser
LDEXTRA =
CCEXTRA =
DIFS		= $(shell ls *.if 2>/dev/null)
GSRCS		= $(DIFS:.if=.cxx)
GHDRS		= $(DIFS:.if=.hxx)
SRCS    = $(shell ls *.cxx 2>/dev/null)
OBJS    = $(SRCS:.cxx=.o)
CFLAGS  = $(CCEXTRA) $(shell pkg-config --cflags eigen3 hmilib-aux) -I../../include -Wall -O2 -g -I/opt/local/include -std=c++11
CC = gcc
CXX= g++


default : $(OBJS)
all : $(OBJS)
depend: $(GHDRS)

%.hxx : %.if
	$(CODEGEN) $<

$(TARGET): $(OBJS)
	ld -r -o $(TARGET) $(OBJS)

%.o : %.cxx
	$(CXX) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(TARGET)

mrproper: clean
	rm -rf *~ $(GSRCS) $(GHDRS)
