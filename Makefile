SOURCEDIR = src
BUILDDIR  = build/

# Pra C
HEADERS = $(shell find . -name '*.hpp')
SOURCES = $(shell find . -name '*.cpp')
OBJFILES = $(patsubst %.cpp, %.o, $(SOURCES))

# Compilador
CC       = g++
# Flags
CFLAGS   = -std=c++11 -c -Wall
LDFLAGS  =
# Nome binário output
TARGET   = tp2

all: build
build: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) && $(CC) -o $(BUILDDIR)$(TARGET) $(OBJFILES) | make cleanO

cleanO:
	rm -f $(shell find . -name '*.o') $(shell find . -name '*.hpp.gch') *~
clean:
	rm -f $(OBJFILES) $(TARGET) $(shell find . -name '*.hpp.gch') *~
run:
	./build/tp2
debug:
	./build/tp2 -d
