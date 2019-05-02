SOURCEDIR = src
BUILDDIR  = build/

# Pra C
HEADERS = $(shell find . -name '*.h')
SOURCES = $(shell find . -name '*.c')
OBJFILES = $(patsubst %.c, %.o, $(SOURCES))

# Pra C++
CPP_HEADERS = $(shell find . -name '*.hpp')
CPP_SOURCES = $(shell find . -name '*.cpp')
CPP_OBJFILES = $(patsubst %.cpp, %.o, $(CPP_SOURCES))

# Compilador
CC       = gcc
# Flags
CFLAGS   = -c -Wall
LDFLAGS  =
# Nome binário output
TARGET   = tp2

all: build
build: $(TARGET)

$(TARGET): $(OBJFILES)
	# $(CC) $(CFLAGS) $(HEADERS) $(SOURCES) $(LDFLAGS) && $(CC) -o $(BUILDDIR)$(TARGET) $(OBJFILES) | make cleanO
	$(CC) $(CFLAGS) $(CFLAGS) $(CPP_HEADERS) $(SOURCES) $(CPP_SOURCES) $(LDFLAGS) && $(CC) -o $(BUILDDIR)$(TARGET) $(OBJFILES) $(CPP_OBJFILES) | make cleanO

cleanO:
	rm -f $(shell find . -name '*.o') $(shell find . -name '*.h.gch') *~
clean:
	rm -f $(OBJFILES) $(TARGET) $(shell find . -name '*.h.gch') *~
run:
	./build/tp2
debug:
	./build/tp2 -d
