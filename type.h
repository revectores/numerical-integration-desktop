#include <vector>

typedef struct _point {
	double x;
	double y;
} point;

typedef struct _interval {
	double left;
	double right;
} interval;

typedef struct _sum_step {
	double sum;
	double step;
} sum_step;

typedef double (* func)(double x);
typedef double (* integral_method)(func f, interval intv, int div_count);

typedef std::vector<point> vpoint;

bool equal_step(vpoint points);