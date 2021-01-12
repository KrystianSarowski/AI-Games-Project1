#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <array>
#include <math.h>

class Tile
{
public:

	Tile();

	void setPosition(sf::Vector2f t_pos);
	void setIsOccupied(bool t_isOccupied);
	void addNeighbour(Tile* t_neighbour);
	void setGoalCost(int t_index, int t_cost);

	std::list<Tile*> getNeighbours() const;
	sf::Vector2f getPosition() const;
	Tile* getNeighbourInDirection(sf::Vector2f t_direction) const;
	bool getIsOccupied() const;
	int getGoalCost(int t_index) const;

private:

	sf::Vector2f m_position;

	std::list<Tile*> m_neighbours;

	bool m_isOccupied;

	std::array<int, 2> m_goalCosts;
};