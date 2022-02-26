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

// TODO: function to get time to set

int start_timer(int values, ...) {
	if (values > 3)
		return 1;

	if (timer_state == RUNNING) {
		printf("%s: timer already running, ret\n", __func__);
		return ERRRUN;
	} else {
		unsigned int arr[values];
		va_list list;
		va_start(list, values);
		for (int i = 0; i < values; ++i) {
			arr[i] = va_arg(list, int);
		}

		timer_state = RUNNING;
		unsigned int to_set, i, hours, minutes, seconds;

		seconds = arr[0] ? arr[0] : 0;
		minutes = arr[1] ? arr[1] : 0;
		hours	= arr[2] ? arr[2] : 0;

		// TODO: don't use *_to_set, only use seconds, minutes and hours and convert them in seconds
		// without using other variable
		// TODO: handle seconds > 60
		int hours_to_set = hours * 3600;
		int minutes_to_set = minutes * 60;
		// TODO: seconds to set if > 60

		to_set = seconds + hours_to_set + minutes_to_set;
		printf("to_set: %d\n", to_set);
		for (i = to_set; i > 0; i--) {
			printf("\r%d", i);
			fflush(stdout);
			sleep(1); /* 1 sec */
		}
		va_end(list);
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
