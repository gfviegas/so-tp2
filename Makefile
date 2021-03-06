SOURCEDIR = src
BUILDDIR  = build/

# Pra C
HEADERS = $(shell find . -name '*.hpp')
SOURCES = $(shell find . -name '*.cpp')
# OBJFILES = $(patsubst %.cpp, %.o, $(SOURCES))

OBJNAMES = $(shell find . -name '*.cpp' -execdir basename '{}' ';')
OBJFILES = $(patsubst %.cpp, %.o, $(OBJNAMES))

# Compilador
CC       = g++
# Flags
CFLAGS   = -Wall -c
LDFLAGS  =
STD = -std=c++11
# Nome binário output
TARGET   = tp2

all: build
build: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(STD) $(CFLAGS) $(SOURCES) $(LDFLAGS)
	$(CC) $(STD) -o $(BUILDDIR)$(TARGET) $(OBJFILES)

cleanO:
	rm -f $(shell find . -name '*.o') $(shell find . -name '*.hpp.gch') *~
clean:
	rm -f $(OBJFILES) $(TARGET) $(shell find . -name '*.hpp.gch') *~
run:
	./build/tp2
debug:
	./build/tp2 -d
