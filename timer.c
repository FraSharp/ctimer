#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "timer.h"

struct timer_time get_current_time() {
	struct timer_time timer_time_struct;

	timer_time_struct.tm_seconds = time(NULL);
	timer_time_struct.time_struct = localtime(&timer_time_struct.tm_seconds);

	return timer_time_struct;
}

enum timer_states timer_state;

int is_timer_running(enum timer_states timer_state) {
	int ret = timer_state == RUNNING ? 1 : 0;
	return ret;
}

int alter_timer_state(void) {
	return 0;
}

void allocate_array(unsigned int dest_array[], int values, ...) {
	va_list list;
	va_start(list, values);

	for (int i = 0; i < values; i++)
		dest_array[i] = va_arg(list, int);

	va_end(list);
}

// TODO: function to get time to set
int get_time_to_set(int values, ...) {
	if (values > 3)
		return ERRVAL;

	unsigned int arr[values], to_set, hours, minutes, seconds;
	allocate_array(arr, values, 20, 1, 0);

	seconds = arr[0] ? arr[0] : 0;
	minutes = arr[1] ? arr[1] : 0;
	hours   = arr[2] ? arr[2] : 0;

	to_set = seconds + (hours * 3600) + (minutes * 60);
	printf("to_set: %d\n", to_set);
	return to_set;
}


int start_timer(int values, ...) {
	if (values > 3)
		return ERRVAL;

	if (timer_state == RUNNING) {
		printf("%s: timer already running, ret\n", __func__);
		return ERRRUN;
	}

	unsigned int to_set, i;
	timer_state = RUNNING;

	// TODO: don't use *_to_set, only use seconds, minutes and hours and convert them in seconds
	// without using other variable
	// TODO: handle seconds > 60
	// int hours_to_set = hours * 3600;
	// int minutes_to_set = minutes * 60;
	// TODO: seconds to set if > 60
	to_set = get_time_to_set(20, 1, 0);
	for (i = to_set; i > 0; i--) {
		printf("\r%d", i);
		fflush(stdout);
		sleep(1); /* 1 sec */
	}

	timer_state = STOPPED;
	return 0;
}

int main(void) {
	struct timer_time timer_func_struct;
	int hours, minutes, seconds;
	timer_func_struct = get_current_time();

	/* time */
	hours = timer_func_struct.time_struct->tm_hour;
	minutes = timer_func_struct.time_struct->tm_min;
	seconds = timer_func_struct.time_struct->tm_sec;

	printf("%d:%d:%d\n", hours, minutes, seconds);
	// need to put an int before any value to set how many values we want to pass as parameters
	timer_state = STOPPED;

	start_timer(3, 20, 1, 10);
	// printf("%d\n", timer_state);		2 = STOPPED

	return 0;
}
