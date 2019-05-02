SOURCEDIR = src
BUILDDIR  = build/

HEADERS = $(shell find . -name '*.h')
SOURCES = $(shell find . -name '*.c')
OBJFILES = $(patsubst %.c, %.o, $(SOURCES))

CC       = gcc
CFLAGS   = -c -Wall
LDFLAGS  =
TARGET   = tp2

all: build
build: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(HEADERS) $(SOURCES) $(LDFLAGS) && $(CC) -o $(BUILDDIR)$(TARGET) $(OBJFILES) | make cleanO

cleanO:
	rm -f $(shell find . -name '*.o') $(shell find . -name '*.h.gch') *~
clean:
	rm -f $(OBJFILES) $(TARGET) $(shell find . -name '*.h.gch') *~
run:
	./build/tp2
analysis:
	./build/tp2 -a
