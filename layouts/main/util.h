#pragma once

#include <string.h>
#include <math.h>

#define zero(v) memset((v), 0, sizeof(*(v)))

static const double EPSILON = 0.001;

double random_double(void)
{
	return (double)rand() / RAND_MAX;
}

typedef struct {
	double x;
	double y;
} vec_t;

vec_t vec_zero(void) {
	vec_t res = {0};
	return res;
}

vec_t vec_norm(vec_t v)
{
	double len = sqrt(v.x * v.x + v.y * v.y);
	if (len > 0.001) {
		v.x /= len;
		v.y /= len;
	} else {
		v.x = 0;
		v.y = 0;
	}
	return v;
}

vec_t vec_scale(vec_t v, double scale)
{
	v.x *= scale;
	v.y *= scale;
	return v;
}

vec_t vec_add(vec_t a, vec_t b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}
