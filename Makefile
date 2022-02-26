CC := clang

timer: timer.c
	$(CC) timer.c -o timer -pedantic -W{all,extra,error} --std=c11 -xc
