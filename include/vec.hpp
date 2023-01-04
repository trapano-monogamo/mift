#pragma once
#include <iostream>

struct vec2 {
	float x = 0.0f;
	float y = 0.0f;

	vec2() = default;
	vec2(float _x, float _y) : x(_x), y(_y) {}
	vec2(const vec2& v) : x(v.x), y(v.y) {}
	vec2& operator=(const vec2& v) = default;

	float magnitude() const;

	static vec2 normalize(const vec2& v);

	static vec2 cross(const vec2& l, const vec2& r);
	static float dot(const vec2& l, const vec2& r);

	static float distance(const vec2& l, const vec2& r);
	static vec2 distancev(const vec2& l, const vec2& r);

	friend vec2 operator+(const vec2& l, const vec2& r);
	friend vec2 operator-(const vec2& l, const vec2& r);
	friend vec2 operator*(const vec2& l, const vec2& r);
	friend vec2 operator/(const vec2& l, const vec2& r);
	friend vec2 operator+(const vec2& l, float r);
	friend vec2 operator-(const vec2& l, float r);
	friend vec2 operator*(const vec2& l, float r);
	friend vec2 operator/(const vec2& l, float r);

	friend vec2 operator-(const vec2& r);

	void operator+=(const vec2& r);
	void operator-=(const vec2& r);
	void operator*=(const vec2& r);
	void operator/=(const vec2& r);
	void operator+=(float r);
	void operator-=(float r);
	void operator*=(float r);
	void operator/=(float r);
	
	friend std::ostream& operator<<(std::ostream& out, const vec2& v);
};
