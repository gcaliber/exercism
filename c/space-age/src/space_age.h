#ifndef SPACE_AGE_H
#define SPACE_AGE_H

#define EARTH_YEAR 31557600

enum { MERCURY, VENUS, EARTH, MARS, JUPITER, SATURN, URANUS, NEPTUNE };

double convert_planet_age(int planet, long seconds);

#endif
