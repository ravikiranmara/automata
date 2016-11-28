# compiler and flags
CC=g++
CFLAGS=  -std=c++11 -Wno-write-strings -g

all:
	$(CC) -c -pthread -Wall zlog.c -o zlog.obj
	$(CC) $(CFLAGS) main.cpp -o project1 zlog.obj -pthread 

Debug:
	all

Release:
	all

clean:
	rm regnfa
	rm zlog.obj
