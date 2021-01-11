#include "MyMath.h"

float MyMath::distance(sf::Vector2f t_vect1, sf::Vector2f t_vect2)
{
    return sqrt(powf(t_vect1.x - t_vect2.x, 2) + powf(t_vect1.y - t_vect2.y, 2));
}
