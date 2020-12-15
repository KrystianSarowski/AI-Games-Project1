#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

enum class OwnerColour
{
	RED,
	GREEN,
	BLANK
};

class Tile
{
public:

	Tile();

	void setPosition(sf::Vector2f t_pos);
	void setOwnerColour(OwnerColour t_ownerColour);
	void setIsOccupied(bool t_isOccupied);
	void addNeighbour(Tile* t_neighbour);

	std::list<Tile*> getNeighbours() const;
	OwnerColour getOwnerColour() const;
	sf::Vector2f getPosition() const;
	bool getIsOccupied() const;

private:

	sf::Vector2f m_position;

	OwnerColour m_ownerColour; 

	std::list<Tile*> m_neighbours;

	bool m_isOccupied;
};