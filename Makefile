CC := clang

timer: timer.c
	$(CC) timer.c -o timer -Wall -Wextra -pedantic -Werror --std=c11 -Ofast
