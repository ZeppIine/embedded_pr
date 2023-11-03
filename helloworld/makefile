OBJECTS = main.o print.o input.o
SRCS = main.c print.c input.c
CC = gcc
CFLAGS = -g -Wall
TARGET = test

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

clean :
	rm -f $(OBJECTS)
	rm -f $(TARGET)

main.o: main.c common.h
print.o: print.c common.h
input.o: input.c common.h
