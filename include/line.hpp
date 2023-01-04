#pragma once
#include "vec.hpp"

struct Line {
	vec2 origin;
	vec2 end;

	Line(vec2 o, vec2 e) : origin(o), end(e) {}
	~Line() = default;

	static bool intersect();
	static vec2 intersection();
	static float distancePointLine(const vec2& p, const Line& l);

	vec2 lerp(float t);
};
