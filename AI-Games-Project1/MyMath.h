#pragma once
#include <SFML/Graphics.hpp>

class MyMath
{
public:

	/// @brief Gets the distance between the passed in two vectors.
	/// 
	/// Uses the distance formula between the passed in two vecotrs.
	/// @param t_vect1 The position of the first point.
	/// @param t_vect2 The position of the second point.
	/// @return the distance between two points.
	static float distance(sf::Vector2f t_vect1, sf::Vector2f t_vect2);

private:

	MyMath();
};

