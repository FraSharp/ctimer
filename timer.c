#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "timer.h"

union timer_time get_current_time() {
	union timer_time timer_time_struct;

	timer_time_struct.tm_seconds = time(NULL);
	timer_time_struct.time_struct = localtime(&timer_time_struct.tm_seconds);

	return timer_time_struct;
}

enum timer_states timer_state;

/* time to set in seconds  */
uint time_to_set(uint seconds, uint minutes, uint hours) {
	return seconds + (hours * 3600) + (minutes * 60);
}

int start_timer(uint seconds, uint minutes, uint hours) {
	uint seconds_to_set, i;
        seconds_to_set = time_to_set(seconds, minutes, hours);

	timer_state = RUNNING;

	// TODO: handle seconds > 60
	for (i = seconds_to_set; i > 0; i--) {
		printf("\r%d remaining", i);
		fflush(stdout);
		sleep(1); /* 1 sec */
	}

	timer_state = STOPPED;
	return 0;
}

int main(void) {
	union timer_time timer_func_struct;
	uint hours, minutes, seconds;
	timer_func_struct = get_current_time();

	/* time */
	hours = timer_func_struct.time_struct->tm_hour;
	minutes = timer_func_struct.time_struct->tm_min;
	seconds = timer_func_struct.time_struct->tm_sec;

	printf("%d:%d:%d\n", hours, minutes, seconds);
	// need to put an int before any value to set how many values we want to pass as parameters
	timer_state = STOPPED;

	start_timer(0, 1, 0);
	// printf("%d\n", timer_state);		2 = STOPPED

	return 0;
}
