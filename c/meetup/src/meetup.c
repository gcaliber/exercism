#include "meetup.h"
#include <string.h>
#include <time.h>

#include <stdio.h>

int month_days(int month, int year);

int meetup_day_of_month(int year, int month, char *day_type_str, char *wday_str)
{
    struct tm start_date;
    
    start_date.tm_sec = 0;
    start_date.tm_min = 0;
    start_date.tm_hour = 0;
    start_date.tm_mday = 1;
    start_date.tm_mon = month - 1;
    start_date.tm_year = year - 1900;
    start_date.tm_isdst = 0;

    time_t t = mktime(&start_date);
    struct tm *date = gmtime(&t);

    int starting_wday = date->tm_wday;
    int target_wday;
    if (strcmp(wday_str, "Sunday") == 0)         { target_wday = 0; }
    else if (strcmp(wday_str, "Monday") == 0)    { target_wday = 1; }
    else if (strcmp(wday_str, "Tuesday") == 0)   { target_wday = 2; }
    else if (strcmp(wday_str, "Wednesday") == 0) { target_wday = 3; }
    else if (strcmp(wday_str, "Thursday") == 0)  { target_wday = 4; }
    else if (strcmp(wday_str, "Friday") == 0)    { target_wday = 5; }
    else if (strcmp(wday_str, "Saturday") == 0)  { target_wday = 6; }
    
    int day = 1;
    if (target_wday > starting_wday) {
        day += target_wday - starting_wday;
    }
    else if (target_wday < starting_wday) {
        day += 7 - (starting_wday - target_wday);
    }
    
    if (strcmp(day_type_str, "teenth") == 0) {
        while (day < 13) {
            day += 7;
        }
        return day;
    }
    else if (strcmp(day_type_str, "first") == 0) {
        return day;
    }
    else if (strcmp(day_type_str, "second") == 0) {
        return day + 7;
    }
    else if (strcmp(day_type_str, "third") == 0) {
        return day + 14;
    }
    else if (strcmp(day_type_str, "fourth") == 0) {
        return day + 21;
    }
    else if (strcmp(day_type_str, "fifth") == 0) {
        day += 28;
        int days_in_month = month_days(month, year);
        if (day > days_in_month) {
            return 0;
        }
        return day;
    }
    else if (strcmp(day_type_str, "last") == 0) {
        int days_in_month = month_days(month, year);
        while (day <= days_in_month) {
            day += 7;
        }
        return day - 7;
    }
    return -1;
}

int is_leapyear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int month_days(int month, int year)
{
    static const int days[2][13] = {
        {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
    return days[is_leapyear(year)][month];
}