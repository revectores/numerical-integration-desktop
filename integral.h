#include "type.h"

double composite_trapezoid_by_points(vpoint points);
double composite_Simpson_by_points(vpoint points);
double composite_trapezoid(func f, interval intv, int div_count);
double composite_Simpson(func f, interval intv, int div_count);
double Romberg(func f, interval intv, int n);
sum_step auto_step_integral(integral_method method, func f, interval intv, double precision);

double ln(double x);
double sqrt_sin(double x);
double sin_over_x(double x);
double exp_over_square_sum(double x);
double ln_over_square_sum(double x);
