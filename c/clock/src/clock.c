#include "clock.h"

void clock(time_text_t time_text, int hour, int minute)
{
    hour += minute / 60;
    hour %= 24;
    minute %= 60;
    
    if (hour < 0) {
        hour += 24;
    }
    if (minute < 0) {
        minute += 60;;
    }
    
    
}

void clock_add(time_text_t time_text, int minute_offset)
{
    
}