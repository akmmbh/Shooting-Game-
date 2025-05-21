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
	Vec2(const sf::Vector2<T>&vec):x(vec.x),y(vec.y){}
//allow automatic conversion to sf::Vector2
//this lets us pass Vec2 into sfml functions
operator sf::Vector2<T>()
{
	return sf::Vector2<T>(x, y);
}

};