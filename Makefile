


CC		:= g++
OBJDIR		:= ./build
CFLAGS_COMMON	:= -Wall -Wshadow -Wextra -Wno-unused-parameter -Werror
CFLAGS_COMMON	+= -std=c++17
CFLAGS_DEBUG	:= $(CFLAGS_COMMON) -O -g
CFLAGS		:= $(CFLAGS_COMMON) -O3

all:		histogram.cpp	map1.cpp	map2.cpp	distrib.cpp	map2order.cpp

histogram: 	histogram.cpp 
		$(CC) histogram.cpp -o histogram $(CFLAGS)

map1: 		map1.cpp
		$(CC) map1.cpp -o map1 $(CFLAGS)

map2: 		map2.cpp
		$(CC) map2.cpp -o map2 $(CFLAGS)

distrib: 	distrib.cpp 
		$(CC) distrib.cpp -o distrib $(CFLAGS)


