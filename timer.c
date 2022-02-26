#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>

enum timer_states {
	RUNNING = 0,
	PAUSED,
	STOPPED
} timer_states;

struct timer_time {
	time_t tm_seconds;
	struct tm *time_struct;
};

struct timer_time get_current_time() {
	struct timer_time timer_time_struct;

	timer_time_struct.tm_seconds = time(NULL);
	timer_time_struct.time_struct = localtime(&timer_time_struct.tm_seconds);

	return timer_time_struct;
}

typedef enum error {
	ERRRUN = 12
} error;

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
	if (timer_state == RUNNING) {
		printf("%s: timer already running, ret\n", __func__);
		return ERRRUN;
	} else {
// TODO: handle (convert) time > 60
		va_list list;
		va_start(list, values);
		timer_state = RUNNING;
		unsigned int to_set, i, hours, minutes, seconds;

		seconds = list[0] ? list[0] : 0;
		minutes = list[1] ? list[1] : 0;
		hours	= list[2] ? list[2] : 0;

		to_set = (seconds + ((minutes / 60) + (hours / 3600)));

		for (i = to_set; i > 0; i--) {
			printf("\r%d", i);
			printf("\n");
			fflush(stdout);
			usleep(300); /* 1 sec */
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

	//printf("%d:%d:%d\n", hours, minutes, seconds);
	// need to put an int before any value to set how many values we want to pass as parameters
	timer_state = STOPPED;
	start_timer(3, 20, 1, 0);
	// printf("%d\n", timer_state);		2 = STOPPED

	return 0;
}
