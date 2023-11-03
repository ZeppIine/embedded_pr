OBJECTS = pr1_main.o pr1_math.o pr1_tTable.o
SRCS = pr1_main.c pr1_math.c pr1_tTable.c
CC = gcc
CFLAGS = -g
TARGET = pr1_test

$(TARGET): $(OBJECTS)
	$(CC) -o  $(TARGET) $(OBJECTS)

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

pr1_main.o: pr1_main.c pr1_common.h
pr1_math.o: pr1_math.c pr1_common.h
pr1_tTable.o: pr1_tTable.c pr1_common.h