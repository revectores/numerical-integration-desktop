#include <vector>

typedef struct _point {
	double x;
	double y;
} point;

typedef struct _interval {
	double left;
	double right;
} interval;

typedef struct _step_sum {
	double step;
	double sum;
} step_sum;

typedef double (* func)(double x);
typedef double (* integral_method)(func f, interval intv, int div_count);


typedef std::vector<point> vpoint;

bool equal_step(vpoint points);