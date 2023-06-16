CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS =

SRCDIR = src
INCDIR = include
BINDIR = bin
OBJDIR = build

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
EXECUTABLE = $(BINDIR)/raytrace.out

.PHONY: all clean compile done

all: compile done

compile: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

done: $(EXECUTABLE)
	rm -f test.ppm
	./bin/raytrace.out >> test.ppm

clean:

	rm -rf $(BINDIR)/* $(OBJDIR)/*
