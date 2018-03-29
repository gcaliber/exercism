#include "triangle.h"

bool is_valid_triangle(triangle_t t);

bool is_equilateral(triangle_t triangle)
{
    if (!triangle.a && !triangle.b && !triangle.c) return false;
    return triangle.a == triangle.b && triangle.a == triangle.c;
}

bool is_isosceles(triangle_t triangle)
{
    bool isosceles = triangle.a == triangle.b || triangle.a == triangle.c || triangle.b == triangle.c;
    if (!isosceles) return false;
    
    return is_valid_triangle(triangle);
}

bool is_scalene(triangle_t triangle)
{
    bool scalene = triangle.a != triangle.b && triangle.a != triangle.c && triangle.b != triangle.c;
    if (!scalene) return false;
    
    return is_valid_triangle(triangle);
}

bool is_valid_triangle(triangle_t t)
{
    double large;
    double small;
    if (t.a == t.b) {
        if (t.a > t.c) {
            large = t.a;
            small = t.c;
        }
        else {
            large = t.c;
            small = t.a;                
        }
    } 
    else {
        if (t.a > t.b) {
            large = t.a;
            small = t.b;
        }
        else {
            large = t.c;
            small = t.b;                
        }
    }
    return small * small * 2 >= large * large;
}