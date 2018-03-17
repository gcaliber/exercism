#include "meetup.h"
#include <string.h>
#include <time.h>

#include <stdio.h>

int meetup_day_of_month(int year, int month, char *day_type, char *day)
{
    struct tm *date;
    
    //date->tm_sec = 0;         /* seconds,  range 0 to 59          */
    //date->tm_min = 0;         /* minutes, range 0 to 59           */
    //date->tm_hour = 0;        /* hours, range 0 to 23             */
    date->tm_mday = 1;        /* day of the month, range 1 to 31  */
    date->tm_mon = month - 1;         /* month, range 0 to 11             */
    date->tm_year = year - 1900;        /* The number of years since 1900   */
    
    time_t start = mktime(date);
    printf("%s\n", ctime(&start));
    
    if (strcmp(day_type, "teenth") == 0) 
    {
        
    }
    else if (strcmp(day_type, "first") == 0)
    {

    }
    else if (strcmp(day_type, "second") == 0)
    {

    }
    else if (strcmp(day_type, "third") == 0)
    {

    }
    else if (strcmp(day_type, "fourth") == 0)
    {

    }
    else if (strcmp(day_type, "fifth") == 0)
    {

    }
    else if (strcmp(day_type, "last") == 0)
    {

    }
    return 0;
}