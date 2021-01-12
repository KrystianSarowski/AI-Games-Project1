#include "Piece.h"

float Piece::s_radius = 11.0f;

Piece::Piece() : m_tile(nullptr)
{
	m_body.setFillColor(sf::Color::White);
	m_body.setRadius(s_radius);
	m_body.setOrigin(sf::Vector2f(s_radius, s_radius));
}

void Piece::setType(PieceType t_type)
{
	m_type = t_type;

	if (m_type == PieceType::GREEN)
	{
		m_body.setFillColor(sf::Color::Green);
	}

	else if (m_type == PieceType::RED)
	{
		m_body.setFillColor(sf::Color::Red);
	}
}

void Piece::setTile(Tile* t_newTile)
{
	m_tile = t_newTile;

	m_body.setPosition(m_tile->getPosition());
}

void Piece::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_body);
}

Tile* Piece::getTile()
{
	return m_tile;
}

PieceType Piece::getType()
{
	return m_type;
}

std::list<Tile*> Piece::getPossibleMoves()
{
	std::list<Tile*> tileList;
	std::list<Tile*> neighbourList = m_tile->getNeighbours();

	bool allTilesEmpty = true;

	for (auto it = neighbourList.begin(); it != neighbourList.end(); ++it)
	{
		if (!(*it)->getIsOccupied())
		{
			tileList.push_back((*it));
		}
		else
		{
			allTilesEmpty = false;
		}
	}

	if (!allTilesEmpty)
	{
		getJumpOverMoves(tileList, m_tile);
	}

	return tileList;
}

void Piece::getJumpOverMoves(std::list<Tile*>& t_moveList, Tile* t_tile)
{
	std::list<Tile*> neighbourList = t_tile->getNeighbours();

	for (auto it = neighbourList.begin(); it != neighbourList.end(); ++it)
	{
		if ((*it)->getIsOccupied())
		{
			Tile* nextTile = (*it)->getNeighbourInDirection((*it)->getPosition() - t_tile->getPosition());

			if (nextTile != nullptr)
			{
				if (!nextTile->getIsOccupied())
				{
					auto tileIt = std::find(t_moveList.begin(), t_moveList.end(), nextTile);

					if (tileIt == t_moveList.end())
					{
						t_moveList.push_back(nextTile);

						getJumpOverMoves(t_moveList, nextTile);
					}
				}
			}
		}
	}
}
