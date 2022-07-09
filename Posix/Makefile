CC := g++
CCFLAGS :=
DBGFLAGS := -g
CCOBJFLAGS := $(CCFLAGS) -c

TARGET = main_1 main_2 main_3 main_4
all: $(TARGET)

LIBS = -lpthread

CLEAN_LIST := $(TARGET)

main_1: main_1.cpp
	$(CC) -o $@ $< $(LIBS)

main_2: main_2.cpp
	$(CC) -o $@ $< $(LIBS)

main_3: main_3.cpp
	$(CC) -o $@ $< $(LIBS)

main_4: main_4.cpp
	$(CC) -o $@ $< $(LIBS)

.PHONY: all
	all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o
	rm -f $(TARGET)