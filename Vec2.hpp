#pragma once
#include<SFML/Graphics.hpp>
#include <math.h>
template<typename T>
class Vec2
{
public:
	T x = 0;
	T y = 0;
	Vec2() = default;
	Vec2(T xin, T yin) : x(xin), y(yin) {};

	//constructor to convert from sf::Vector2
	Vec2(const sf::Vector2<T>& vec) :x(vec.x), y(vec.y) {};
//allow automatic conversion to sf::Vector2
//this lets us pass Vec2 into sfml functions
operator sf::Vector2<T>()
{
	return sf::Vector2<T>(x, y);
}
Vec2 operator +(const Vec2& rhs) const {
	return Vec2(x + rhs.x, y + rhs.y);
}
Vec2 operator - (const Vec2& rhs)const {
	return Vec2(x - rhs.x, y - rhs.y);
}
Vec2 operator *(const T value)const {
	return Vec2(x * value, y * value);

}
Vec2 operator /(const T value)const {
	return (x / value, y / value);
}
bool operator ==(const Vec2& rhs)const {
	return (x == rhs.x && y == rhs.y);
}
bool operator!=(const Vec2& rhs)const {
	return (x != rhs.x || y != rhs.y);
}
void operator+=(const Vec2& rhs) {
	x += rhs.x;
	y += rhs.y;
}
void operator -= (const Vec2& rhs) {
	x -= rhs.x;
	y -= rhs.y;

}
void operator *= (const T value) {
	x *= value;
	y *= value;
}
void operator /= (const T val) {
	x /= val;
	y /= val;
	
}
float dist(const Vec2 & rhs)const {
	return sqrt(pow(x - rhs.x, 2) + pow(y - rhs.y, 2));
}
};
using Vec2f = Vec2<float>;