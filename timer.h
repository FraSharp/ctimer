#include <time.h>
#include <stdio.h>

enum timer_states {
	RUNNING = 0,
	PAUSED,
	STOPPED
};

union timer_time {
	time_t tm_seconds;
	struct tm *time_struct;
};

typedef enum error {
	ERRRUN = 12,
	ERRVAL = 24
} error;

typedef unsigned int uint;

union timer_time get_current_time(void);
uint time_to_set(uint seconds, uint minutes, uint hours);
int start_timer(uint seconds, uint minutes, uint hours);
int main(void);

