#include "math.h"

double factorial(int a) {
	double result = a;
	while (--a)
		result *= a;
	return result;
}
