#include "Board.h"

Board::Board(sf::Vector2u t_windowSize)
{
	createGrid(t_windowSize);
	connectTiles();
	generateCosts();
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

	for (int j = 0; j < m_piecesGreen.size(); j++)
	{
		m_piecesGreen[j]->render(t_window);
		m_piecesRed[j]->render(t_window);
	}
}

std::vector<Piece*> Board::getPieces(PieceType t_type)
{
	if (t_type == PieceType::GREEN)
	{
		return m_piecesGreen;
	}

	else
	{
		return m_piecesRed;
	}

	return std::vector<Piece*>();
}

int Board::calculateValue(PieceType t_type)
{
	int totalValue1 = 0;
	int totalValue2 = 0;

	if (t_type == PieceType::GREEN)
	{
		for (int i = 0; i < m_piecesGreen.size(); i++)
		{
			totalValue1 += m_piecesGreen[i]->getTile()->getGoalCost(static_cast<int>(PieceType::GREEN));
		}

		for (int j = 0; j < m_piecesRed.size(); j++)
		{
			totalValue2 += m_piecesRed[j]->getTile()->getGoalCost(static_cast<int>(PieceType::RED));
		}
	}

	else
	{
		for (int i = 0; i < m_piecesGreen.size(); i++)
		{
			totalValue2 += m_piecesGreen[i]->getTile()->getGoalCost(static_cast<int>(PieceType::GREEN));
		}

		for (int j = 0; j < m_piecesRed.size(); j++)
		{
			totalValue1 += m_piecesRed[j]->getTile()->getGoalCost(static_cast<int>(PieceType::RED));
		}
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
				m_greenGoalTiles.push_back(tile);
			}

			m_grid.push_back(tile);
		}
	}

	m_furthestGoalTiles[0] = m_grid[m_grid.size() - 1];

	startPos.y = startPos.y + offSetY * (m_MAX_ROW_LENGTH - 5);

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
					m_redGoalTiles.push_back(tile);
				}

				m_grid.push_back(tile);
			}
		}
	}

	m_furthestGoalTiles[1] = m_grid[m_grid.size() - 1];
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

void Board::generateCosts()
{
	for (int i = 0; i < m_furthestGoalTiles.size(); i++)
	{
		m_furthestGoalTiles[i]->setGoalCost(i, 0);

		std::queue<Tile*> tileQueue;

		tileQueue.push(m_furthestGoalTiles[i]);

		while (!tileQueue.empty())
		{
			std::list<Tile*> neighbourList = tileQueue.front()->getNeighbours();
			int currenCost = tileQueue.front()->getGoalCost(i);
			std::list<Tile*>::iterator it;

			for (it = neighbourList.begin(); it != neighbourList.end(); ++it)
			{
				if ((*it)->getGoalCost(i) == -1)
				{
					(*it)->setGoalCost(i, currenCost + 1);
					tileQueue.push(*it);
				}
			}

			tileQueue.pop();
		}
	}
}

void Board::createPieces()
{
	for (Tile* goalTile : m_greenGoalTiles)
	{
		Piece* newPiece = new Piece();
		newPiece->setType(PieceType::GREEN);
		newPiece->setTile(goalTile);
		goalTile->setIsOccupied(true);

		m_piecesGreen.push_back(newPiece);
	}

	for (Tile* goalTile : m_redGoalTiles)
	{
		Piece* newPiece = new Piece();
		newPiece->setType(PieceType::RED);
		newPiece->setTile(goalTile);
		goalTile->setIsOccupied(true);

		m_piecesRed.push_back(newPiece);
	}
}

bool Board::checkForWin(PieceType t_type)
{
	int count = 0;

	if (t_type == PieceType::GREEN)
	{
		for (Piece* piece : m_piecesGreen)
		{
			for (Tile* goalTile : m_redGoalTiles)
			{
				if (piece->getTile() == goalTile)
				{
					count += 1;
					break;
				}
			}
		}

		if (count == m_piecesGreen.size())
		{
			return true;
		}
	}

	else
	{
		for (Piece* piece : m_piecesRed)
		{
			for (Tile* goalTile : m_greenGoalTiles)
			{
				if (piece->getTile() == goalTile)
				{
					count += 1;
					break;
				}
			}
		}

		if (count == m_piecesRed.size())
		{
			return true;
		}
	}

	return false;
}