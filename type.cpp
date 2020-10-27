#include "type.h"

bool equal_step(vpoint points){
	if (points.size() <= 2){
		return true;
	}

	double diff = points[1].x - points[0].x;
	for (int i = 1; i < points.size()-1; i++){
		double ndiff = points[i+1].x - points[i].x;
		if (ndiff - diff > 0.00001){
			return false;
		}
		diff = ndiff;
	}
	return true;
}
