#include <ostream>
#include <vec.hpp>
#include <cmath>

float vec2::magnitude() const { return sqrt(x*x + y*y); }

vec2 vec2::normalize(const vec2& v) {
	return v / v.magnitude();
}

// vec2 vec2::cross(const vec2& l, const vec2& r) { }
// float vec2::dot(const vec2& l, const vec2& r) { }

float vec2::distance(const vec2& l, const vec2& r) {
	return sqrt((l.x - r.x) * (l.x - r.x) + (l.y - r.y) * (l.y - r.y));
}

vec2 vec2::distancev(const vec2& l, const vec2& r) {
	return vec2(r.x - l.x, r.y - l.y);
}

vec2 operator+(const vec2& l, const vec2& r) { return vec2(l.x + r.x, l.y + r.y); }
vec2 operator-(const vec2& l, const vec2& r) { return vec2(l.x - r.x, l.y - r.y); }
vec2 operator*(const vec2& l, const vec2& r) { return vec2(l.x * r.x, l.y * r.y); }
vec2 operator/(const vec2& l, const vec2& r) { return vec2(l.x / r.x, l.y / r.y); }

vec2 operator+(const vec2& l, float r) { return vec2(l.x + r, l.y + r); }
vec2 operator-(const vec2& l, float r) { return vec2(l.x - r, l.y - r); }
vec2 operator*(const vec2& l, float r) { return vec2(l.x * r, l.y * r); }
vec2 operator/(const vec2& l, float r) { return vec2(l.x / r, l.y / r); }

void vec2::operator+=(const vec2& r) {
	this->x += r.x;
	this->y += r.y;
}
void vec2::operator-=(const vec2& r) {
	this->x -= r.x;
	this->y -= r.y;
}
void vec2::operator*=(const vec2& r) {
	this->x *= r.x;
	this->y *= r.y;
}
void vec2::operator/=(const vec2& r) {
	this->x /= r.x;
	this->y /= r.y;
}

void vec2::operator+=(float r) {
	this->x += r;
	this->y += r;
}
void vec2::operator-=(float r) {
	this->x -= r;
	this->y -= r;
}
void vec2::operator*=(float r) {
	this->x *= r;
	this->y *= r;
}
void vec2::operator/=(float r) {
	this->x /= r;
	this->y /= r;
}

std::ostream& operator<<(std::ostream& out, const vec2& v) {
	out << "{" << v.x << ", " << v.y << "}";
	return out;
}
