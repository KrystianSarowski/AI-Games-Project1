#include "Board.h"

Board::Board(sf::Vector2u t_windowSize)
{
	createGrid(t_windowSize);
	createPieces();
}

Tile* Board::selectTile(sf::Vector2f t_mousePos)
{
	for (int i = 0; i < m_grid.size(); i++)
	{
		if (MyMath::distance(m_grid[i]->getPosition(), t_mousePos) <= m_TILE_RADIUS)
		{
			return m_grid[i];
		}
	}

	return nullptr;
}

void Board::render(sf::RenderWindow& t_window)
{
	sf::CircleShape tile;

	tile.setRadius(m_TILE_RADIUS-4.0f);
	tile.setOrigin(sf::Vector2f(m_TILE_RADIUS - 4.0f, m_TILE_RADIUS - 4.0f));
	tile.setFillColor(sf::Color(128, 128, 128));
	tile.setOutlineThickness(3.0f);
	tile.setOutlineColor(sf::Color::Black);
	
	for (int i = 0; i < m_grid.size(); i++)
	{
		tile.setPosition(m_grid[i]->getPosition());
		t_window.draw(tile);
	}

	for (int i = 0; i < m_pieces.size(); i++)
	{
		for (int j = 0; j < m_pieces[i].size(); j++)
		{
			m_pieces[i][j]->render(t_window);
		}
	}
}

std::vector<Piece*> Board::getPieces(PieceType t_type)
{
	return m_pieces[static_cast<int>(t_type)];
}

int Board::calculateValue(PieceType t_type)
{
	int totalValue1 = 0;
	int totalValue2 = 0;

	int typeIndex1 = static_cast<int>(t_type);
	int typeIndex2 = (typeIndex1 + 1) % 2;

	for (int i = 0; i < m_pieces[typeIndex1].size(); i++)
	{
		totalValue1 += m_pieces[typeIndex1][i]->getTile()->getTotalGoalCost(typeIndex2);
	}

	for (int i = 0; i < m_pieces[typeIndex2].size(); i++)
	{
		totalValue2 += m_pieces[typeIndex2][i]->getTile()->getTotalGoalCost(typeIndex1);
	}

	return totalValue2 - totalValue1;
}

void Board::createGrid(sf::Vector2u t_windowSize)
{
	float offSetX = (m_TILE_RADIUS + 1.0f) * 2;
	float offSetY = offSetX * sinf(3.14f / 3);

	sf::Vector2f startPos;

	startPos.x = (t_windowSize.x - (offSetX * m_MAX_ROW_LENGTH)) / 2 + (offSetX / 2);
	startPos.y = (t_windowSize.y - (offSetY * (m_MAX_ROW_LENGTH - 5))) / 2;

	std::vector<Tile*> furthestTiles;
	std::vector<Tile*> greenGoalTiles;

	for (int count = m_MAX_ROW_LENGTH; count > 0; count--)
	{
		for (int x = 0; x < count; x++)
		{
			Tile* tile = new Tile();

			sf::Vector2f pos;

			pos.x = startPos.x + (x * offSetX) + (offSetX / 2) * (m_MAX_ROW_LENGTH - count);
			pos.y = startPos.y + offSetY * (m_MAX_ROW_LENGTH - count);
			tile->setPosition(pos);

			if (count < 5)
			{
				greenGoalTiles.push_back(tile);
			}

			m_grid.push_back(tile);
		}
	}

	m_goalTiles.push_back(greenGoalTiles);
	furthestTiles.push_back(m_grid[m_grid.size() - 1]);

	startPos.y = startPos.y + offSetY * (m_MAX_ROW_LENGTH - 5);

	std::vector<Tile*> redGoalTiles;

	for (int count = m_MAX_ROW_LENGTH; count > 0; count--)
	{
		for (int x = 0; x < count; x++)
		{
			Tile* tile = new Tile();

			sf::Vector2f pos;

			pos.x = startPos.x + (x * offSetX) + (offSetX / 2) * (m_MAX_ROW_LENGTH - count);
			pos.y = startPos.y - offSetY * (m_MAX_ROW_LENGTH - count);
			tile->setPosition(pos);

			auto it = std::find_if(m_grid.begin(), m_grid.end(), [=](const Tile* obj)
			{
				return MyMath::distance(obj->getPosition(), tile->getPosition()) < 1;
			});

			if (it == m_grid.end())
			{
				if (count < 5)
				{
					redGoalTiles.push_back(tile);
				}

				m_grid.push_back(tile);
			}
		}
	}

	m_goalTiles.push_back(redGoalTiles);
	furthestTiles.push_back(m_grid[m_grid.size() - 1]);

	connectTiles();
	generateDistanceCosts(furthestTiles);
}

void Board::connectTiles()
{
	float maxTileOffset = (m_TILE_RADIUS + 1.0f) * 2;

	for (int i = 0; i < m_grid.size(); i++)
	{
		for (int j = 0; j < m_grid.size(); j++)
		{
			if (i != j)
			{
				if (maxTileOffset >= MyMath::distance(m_grid[i]->getPosition(), m_grid[j]->getPosition()))
				{
					m_grid[i]->addNeighbour(m_grid[j]);
				}
			}
		}
	}
}

void Board::generateDistanceCosts(std::vector<Tile*> t_furthestGoalTiles)
{
	for (int i = 0; i < t_furthestGoalTiles.size(); i++)
	{
		sf::Vector2f goalTilePos = t_furthestGoalTiles[i]->getPosition();
		t_furthestGoalTiles[i]->setDistanceToGoal(i, 0);
		t_furthestGoalTiles[i]->setVerticalDistanctToGoal(i, 0);

		std::queue<Tile*> tileQueue;

		tileQueue.push(t_furthestGoalTiles[i]);

		while (!tileQueue.empty())
		{
			std::list<Tile*> neighbourList = tileQueue.front()->getNeighbours();
			std::list<Tile*>::iterator it;

			for (it = neighbourList.begin(); it != neighbourList.end(); ++it)
			{
				if ((*it)->getTotalGoalCost(i) == -2)
				{
					(*it)->setDistanceToGoal(i, MyMath::distance(goalTilePos, (*it)->getPosition()));
					(*it)->setVerticalDistanctToGoal(i, abs(goalTilePos.y - (*it)->getPosition().y));
					tileQueue.push(*it);
				}
			}

			tileQueue.pop();
		}
	}
}

void Board::createPieces()
{
	for (int i = 0; i < m_goalTiles.size(); i++)
	{
		PieceType pieceType = static_cast<PieceType>(i);

		std::vector<Piece*> colouredPieces;

		for (Tile* goalTile : m_goalTiles[i])
		{
			Piece* newPiece = new Piece();
			newPiece->setType(pieceType);
			newPiece->setTile(goalTile);
			goalTile->setIsOccupied(true);

			colouredPieces.push_back(newPiece);
		}

		m_pieces.push_back(colouredPieces);
	}
}

bool Board::checkForWin(PieceType t_type)
{
	int count = 0;

	int typeIndex1 = static_cast<int>(t_type);
	int typeIndex2 = (typeIndex1 + 1) % 2;

	for (Piece* piece : m_pieces[typeIndex1])
	{
		for (Tile* goalTile : m_goalTiles[typeIndex2])
		{
			if (piece->getTile() == goalTile)
			{
				count += 1;
				break;
			}
		}
	}

	if (count == m_pieces[typeIndex1].size())
	{
		return true;
	}

	return false;
}

void Board::restart()
{
	for (int i = 0; i < m_pieces.size(); i++)
	{
		for (Piece* piece : m_pieces[i])
		{
			piece->getTile()->setIsOccupied(false);
			piece->setTile(nullptr);
		}
	}

	for (int i = 0; i < m_pieces.size(); i++)
	{
		for (int j = 0; j < m_pieces[i].size(); j++)
		{
			m_pieces[i][j]->setTile(m_goalTiles[i][j]);
			m_goalTiles[i][j]->setIsOccupied(true);
		}
	}
}
