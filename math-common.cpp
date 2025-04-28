#include "math-common.h"

float Lerp(float a, float b, float t) {
	return a + (b - a) * t;
}

float Rand01() {
	return (float)rand() / ((float)RAND_MAX + 1.0f);
}

float Schlick(float cosine, float ref_idx) {
	float r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + ((1 - r0) * pow(1 - cosine, 5));
}
