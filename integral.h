#include "type.h"

double composite_trapezoid_by_points(vpoint points);
double composite_Simpson_by_points(vpoint points);
double composite_trapezoid(func f, interval intv, int div_count);
double composite_Simpson(func f, interval intv, int div_count);
double auto_step_integral(integral_method method, func f, interval intv, double precision);
double Romberg(vpoint points, double precision);
