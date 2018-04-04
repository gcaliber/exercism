#include "complex_numbers.h"
#include <math.h>

complex_t c_add(complex_t a, complex_t b)
{
   complex_t result;
   result.real = a.real + b.real;
   result.imag = a.imag + b.imag;
   return result;
}

complex_t c_sub(complex_t a, complex_t b)
{
   complex_t result;
   result.real = a.real - b.real;
   result.imag = a.imag - b.imag;
   return result;
}

complex_t c_mul(complex_t a, complex_t b)
{
   complex_t result;
   result.real = a.real * b.real - (a.imag * b.imag);
   result.imag = a.real * b.imag + b.real * a.imag;
   return result;
}

complex_t c_div(complex_t a, complex_t b)
{
   complex_t conjugate = c_conjugate(b);
   complex_t numerator = c_mul(a, conjugate);
   complex_t denominator = c_mul(b, conjugate);
   complex_t result;
   result.real = numerator.real / denominator.real;
   result.imag = numerator.imag / denominator.real;
   return result;
}

double c_abs(complex_t x)
{
   return sqrt(pow(x.real, 2) + pow(x.imag, 2));
}

complex_t c_conjugate(complex_t x)
{
   complex_t result = { x.real, -1 * x.imag };
   return result;
}

double c_real(complex_t x)
{
   return x.real;
}

double c_imag(complex_t x)
{
   return x.imag;
}

complex_t c_exp(complex_t x)
{
   complex_t a = { exp(x.real), 0 };
   complex_t b = { cos(x.imag), sin(x.imag) };
   return c_mul(a, b);
}