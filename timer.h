#include <time.h>
#include <stdio.h>

enum timer_states {
	RUNNING = 0,
	PAUSED,
	STOPPED
};

struct timer_time {
	time_t tm_seconds;
	struct tm *time_struct;
};

struct timer_time get_current_time();

typedef enum error {
	ERRRUN = 12,
	ERRVAL = 24
} error;
