CC = gcc
CFLAGS = -g
LIBS = -ljpeg


all: main

main: main.o jpeg_manage.o k_means.o
	$(CC) $^ -o $@ $(LIBS)

main.o: main.c jpeg_manage.h k_means.h

jpeg_manage.o: jpeg_manage.h jpeg_manage.c

k_means.o: k_means.h k_means.c

clean:
	rm -rf k_means.o jpeg_manage.o main main.o

test: 
	./main goddess_gaussian.jpg result_gaussian.jpg
	./main goddess.jpg result_normal.jpg