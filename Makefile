SRCS = main.c
FLAGS = -Wall -Werror --std=c99
CC = gcc

all: main.c
	$(CC) $(FLAGS) $(SRCS) -o main && ./main
