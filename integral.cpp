#include "integral.h"
#include <cmath>
#include <cstdio>

double square(double x){
	return x * x;
}

double ln(double x){
	return log(x);
}

double sqrt_sin(double x){
	return sqrt(4 - pow(sin(x), 2));
}

double sin_over_x(double x){
	return sin(x) / x;
}

double exp_over_square_sum(double x){
	return exp(x) / (4 + x * x);
}

double ln_over_square_sum(double x){
	return ln(1 + x) / (1 + x * x);
}


double composite_trapezoid_by_points(vpoint points){
	if ((points.size() < 2) || (!equal_step(points))) {
		return -1;
	}

	double step = points[1].x - points[0].x;
	double coef = 0.5 * step;

	double sum = points.front().y + points.back().y;
	for (int i = 1; i < points.size() - 1; i++){
		sum += 2 * points[i].y;
	}

	sum *= coef;
	return sum;
}


double composite_Simpson_by_points(vpoint points){
	if ((points.size() < 3) || (points.size() % 2 == 0) || (!equal_step(points))) {
		return -1;
	}

	double step = points[1].x - points[0].x;
	double coef = 1.0 / 3.0 * step;

	double sum = points.front().y + points.back().y;
	for (int i = 1; i < points.size() - 1; i += 2){
		sum += 4 * points[i].y;
	}
	for (int i = 2; i < points.size() - 1; i += 2){
		sum += 2 * points[i].y;
	}

	sum *= coef;
	return sum;
}


double composite_trapezoid(func f, interval intv, int div_count){
	vpoint points;

	double x = intv.left;
	double step = (intv.right - intv.left) / div_count;

	for (int i = 0; i <= div_count; i++){
		points.push_back({x, f(x)});
		x += step;
	}

	double sum = composite_trapezoid_by_points(points);
	return sum;
}


double composite_Simpson(func f, interval intv, int div_count){
	vpoint points;

	double x = intv.left;
	double step = (intv.right - intv.left) / div_count;

	for (int i = 0; i <= div_count; i++){
		points.push_back({x, f(x)});
		x += step;
	}

	double sum = composite_Simpson_by_points(points);
	return sum;
}


double auto_step_integral(integral_method method, func f, interval intv, double precision) {
	if (precision == 0){
		return -1;
	}

	int div_count = 1;
	double sum = method(f, intv, div_count);

	while(true){
		div_count *= 2;
		double nsum = method(f, intv, div_count);
		if (fabs(sum - nsum) < precision){
			sum = nsum;
			// double best_step = (intv.right - intv.left) / div_count;
			// return {best_step, sum};
			return sum;
		}
		sum = nsum;
	}
}



double Romberg(func f, interval intv, double precision){
	if (precision == 0) {
		return -1;
	}

	std::vector<std::vector<double>> R;

	int k = -1;

	while(true){
		fflush(NULL);
		k++;
		int div_count = pow(2, k);
		R.push_back({composite_trapezoid(f, intv, div_count)});
		if (k == 0) {
			continue;
		}
		for (int i = 0; i < k; i++){
			R.back().push_back(R[k][i] + (R[k][i] - R[k-1][i])/(pow(4, i+1)-1));
		}
		printf("R[%d][%d]=%f, R[%d][%d]=%f\n", k, k, R[k][k], k-1, k-1, R[k-1][k-1]);
		if (fabs(R[k][k] - R[k-1][k-1]) < precision) {
			return R[k][k];
		}
	}
}


/*
int main(){
	vpoint points {
		{0.6, 5.7}, {0.8, 4.6}, {1.0, 3.5}, {1.2, 3.7}, {1.4, 4.9}, {1.6, 5.2}, {1.8, 5.5}
	};

	//double trapezoid_integral = composite_trapezoid(square, {0, 1}, 2);
	//double trapezoid_integral2 = auto_step_integral(composite_trapezoid, square, {0, 1}, 0.5);
	//double Simpson_integral = composite_Simpson(square, {0, 1}, 4);
	double Romberg_integral = Romberg(ln, {1, 2}, 0.0001);
	printf("%f", Romberg_integral);

	return 0;
}
*/