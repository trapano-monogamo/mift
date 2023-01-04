#include <cmath>
#include "line.hpp"

float _lerp(float a, float b, float t) {
	return a + (b-a)*t;
}

bool Line::intersect() {
}

vec2 Line::intersection() {
}

float Line::distancePointLine(const vec2& p, const Line& l) {
	float m = (l.end.y - l.origin.y) / (l.end.x - l.origin.x);
	return fabs(-m*p.x + p.y + m*l.origin.x - l.origin.y) / sqrt(m*m + 1);
}

vec2 Line::lerp(float t) {
}
