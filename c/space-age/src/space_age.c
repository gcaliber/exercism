#include "space_age.h"

double convert_planet_age(int planet, long seconds) {
    switch (planet) {
        case EARTH:
            return seconds / EARTH_YEAR;
        case MERCURY:
            return seconds / MERCURY_YEAR;
        case VENUS:
            return seconds / VENUS_YEAR;
        case MARS:
            return seconds / MARS_YEAR;
        case JUPITER:
            return seconds / JUPITER_YEAR;
        case SATURN:
            return seconds / SATURN_YEAR;
        case URANUS:
            return seconds / URANUS_YEAR;
        case NEPTUNE:
            return seconds / NEPTUNE_YEAR;
    }
    return -1;
}