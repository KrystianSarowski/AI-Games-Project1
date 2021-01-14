#include "Tile.h"

Tile::Tile() :
	m_isOccupied(false),
	m_position(sf::Vector2f(0.0f,0.0f))
{
	m_distanceToGoals[0] = -1;
	m_distanceToGoals[1] = -1;

	m_verticalDistanceToGoals[0] = -1;
	m_verticalDistanceToGoals[1] = -1;
}

void Tile::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
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

void Tile::setDistanceToGoal(int t_index, int t_cost)
{
	if (t_index < m_distanceToGoals.size())
	{
		m_distanceToGoals[t_index] = t_cost;
	}
}

void Tile::setVerticalDistanctToGoal(int t_index, int t_cost)
{
	if (t_index < m_verticalDistanceToGoals.size())
	{
		m_verticalDistanceToGoals[t_index] = t_cost;
	}
}

std::list<Tile*> Tile::getNeighbours() const
{
	return m_neighbours;
}

sf::Vector2f Tile::getPosition() const
{
	return m_position;
}

Tile* Tile::getNeighbourInDirection(sf::Vector2f t_direction) const
{
	int temp = static_cast<int>(t_direction.x * 100);
	t_direction.x = temp / 100.0f;

	temp = static_cast<int>(t_direction.y * 100);
	t_direction.y = temp / 100.0f;

	for (auto it = m_neighbours.begin(); it != m_neighbours.end(); ++it)
	{
		sf::Vector2f vector = (*it)->getPosition() - m_position;

		temp = static_cast<int>(vector.x * 100);
		vector.x = temp / 100.0f;

		temp = static_cast<int>(vector.y * 100);
		vector.y = temp / 100.0f;

		if (t_direction == vector)
		{
			return (*it);
		}
	}

	return nullptr;
}

bool Tile::getIsOccupied() const
{
	return m_isOccupied;
}

int Tile::getTotalGoalCost(int t_index) const
{
	return m_distanceToGoals[t_index] + m_verticalDistanceToGoals[t_index];
}
