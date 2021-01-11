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

	tile.setRadius(10);
	tile.setOrigin(sf::Vector2f(10.0f, 10.0f));
	tile.setFillColor(sf::Color::Blue);

	for (int i = 0; i < m_grid.size(); i++)
	{
		tile.setPosition(m_grid[i]->getPosition());
		t_window.draw(tile);
	}

	for (int j = 0; j < m_pieces.size(); j++)
	{
		m_pieces[j]->render(t_window);
	}
}

std::vector<Piece*> Board::getPieces()
{
	return m_pieces;
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

			if (count < 5)
			{
				tile->setOwnerColour(OwnerColour::GREEN);
			}

			tile->setPosition(pos);

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
					tile->setOwnerColour(OwnerColour::RED);
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
	for (int i = 0; i < m_grid.size(); i++)
	{
		if (m_grid[i]->getOwnerColour() == OwnerColour::GREEN)
		{
			Piece* newPiece = new Piece();
			newPiece->setType(PieceType::GREEN);
			newPiece->setTile(m_grid[i]);
			m_grid[i]->setIsOccupied(true);

			m_pieces.push_back(newPiece);
		}

		else if (m_grid[i]->getOwnerColour() == OwnerColour::RED)
		{
			Piece* newPiece = new Piece();
			newPiece->setType(PieceType::RED);
			newPiece->setTile(m_grid[i]);
			m_grid[i]->setIsOccupied(true);

			m_pieces.push_back(newPiece);
		}
	}
}
