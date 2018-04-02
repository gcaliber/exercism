#include "gigasecond.h"
#include <stdbool.h>

time_t my_construct_date(int year, int month, int day, int hour, int min, int sec)
{
   struct tm date;
   date.tm_year = year - 1900;
   date.tm_mon = month - 1;
   date.tm_mday = day;
   date.tm_hour = hour;
   date.tm_min = min;
   date.tm_sec = sec;
   date.tm_isdst = 0;
   return mktime(&date);
}

long seconds_in_year(int year);
long seconds_in_month(int month, bool leapyear);
long remaining_seconds_in_starting_year(time_t date, int year);

time_t gigasecond_after(time_t date) {
    int year = gmtime(&date)->tm_year + 1901;
    long seconds = remaining_seconds_in_starting_year(date, year);
    
    int month = 1, day = 1, hour = 0, min = 0, sec = 0;
    long year_seconds, month_seconds;

    while (seconds < 1e9) {
        year_seconds = seconds_in_year(year++);
        seconds += year_seconds;
    }
    if (seconds > 1e9) {
        seconds -= year_seconds;
        year--;
    }

    bool leapyear = year_seconds == LEAPYEAR_SECONDS;
    while (seconds < 1e9) {
        month_seconds = seconds_in_month(month++, leapyear);
        seconds += month_seconds;
    }
    if (seconds > 1e9) {
        seconds -= month_seconds;
        month--;
    }

    while (seconds < 1e9) {
        seconds += DAY_SECONDS;
        day++;
    }
    if (seconds > 1e9) {
        seconds -= DAY_SECONDS;
        day--;
    }

    while (seconds < 1e9) {
        seconds += HOUR_SECONDS;
        hour++;
    }
    if (seconds > 1e9) {
        seconds -= HOUR_SECONDS;
        hour--;
    }

    while (seconds < 1e9) {
        seconds += MINUTE_SECONDS;
        min++;
    }
    if (seconds > 1e9) {
        seconds -= MINUTE_SECONDS;
        min--;
    }

    while (seconds != 1e9) {
        seconds += 1;
        sec++;
    }

    return my_construct_date(year, month, day, hour, min, sec);
}

long seconds_in_year(int year) {
    if (year % 400 == 0) return LEAPYEAR_SECONDS;
    if (year % 100 == 0) return YEAR_SECONDS;
    if (year % 4 == 0)   return LEAPYEAR_SECONDS;
    return YEAR_SECONDS;
}

long seconds_in_month(int month, bool leapyear) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return MONTH_31_SECONDS;
        case 4:
        case 6:
        case 9:
        case 11:
            return MONTH_30_SECONDS;
        case 2:
            if (leapyear) return MONTH_29_SECONDS;
            else return MONTH_28_SECONDS;
    }
    return -1;
}

long remaining_seconds_in_starting_year(time_t date, int year) {
    time_t new_date = my_construct_date(year, 1, 1, 0, 0, 0);
    return (long) difftime(new_date, date);
}