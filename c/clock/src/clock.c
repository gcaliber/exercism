#include "clock.h"
#include <stdio.h>
#include <stdlib.h>

void clock(time_text_t time_text, int hour, int minute)
{
    hour += minute / 60;
    hour %= 24;
    minute %= 60;
    
    if (minute < 0) {
        hour -= 1;
        minute += 60;;
    }
    if (hour < 0) {
        hour += 24;
    }
    
    sprintf(time_text, "%02d:%02d", hour, minute);
}

void clock_add(time_text_t time_text, int minute_offset)
{
    char *ptr;
    int hour = (int) strtol(time_text, &ptr, 10);
    int minute = (int) strtol(&time_text[3], &ptr, 10);
    minute += minute_offset;
    clock(time_text, hour, minute);
}