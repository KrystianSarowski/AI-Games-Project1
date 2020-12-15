#include "Tile.h"

Tile::Tile() :
	m_ownerColour(OwnerColour::BLANK),
	m_isOccupied(false),
	m_position(sf::Vector2f(0.0f,0.0f))
{

}

void Tile::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
}

void Tile::setOwnerColour(OwnerColour t_ownerColour)
{
	m_ownerColour = t_ownerColour;
}

void Tile::setIsOccupied(bool t_isOccupied)
{
	m_isOccupied = t_isOccupied;
}

void Tile::addNeighbour(Tile* t_neighbour)
{
	auto it = std::find(m_neighbours.begin(), m_neighbours.end(), t_neighbour);

	if (it == m_neighbours.end())
	{
		m_neighbours.push_back(t_neighbour);
	}
}

std::list<Tile*> Tile::getNeighbours() const
{
	return m_neighbours;
}

OwnerColour Tile::getOwnerColour() const
{
	return m_ownerColour;
}

sf::Vector2f Tile::getPosition() const
{
	return m_position;
}

bool Tile::getIsOccupied() const
{
	return m_isOccupied;
}
