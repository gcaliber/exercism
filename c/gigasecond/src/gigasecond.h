#ifndef GIGASECOND_H
#define GIGASECOND_H

#include <time.h>

#define YEAR_SECONDS     31536000
#define LEAPYEAR_SECONDS 31622400
#define MONTH_28_SECONDS 2419200
#define MONTH_29_SECONDS 2505600
#define MONTH_30_SECONDS 2592000
#define MONTH_31_SECONDS 2678400
#define DAY_SECONDS      86400
#define HOUR_SECONDS     3600
#define MINUTE_SECONDS   60

time_t gigasecond_after(time_t date);

#endif
