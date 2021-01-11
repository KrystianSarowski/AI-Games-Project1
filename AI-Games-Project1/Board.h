#pragma once
#include "Tile.h"
#include "Piece.h"
#include "MyMath.h"
#include <array>
#include <queue>

class Board
{
public:

	Board(sf::Vector2u t_windoSize);

	Tile* selectTile(sf::Vector2f t_mousePos);
	void render(sf::RenderWindow& t_window);

	std::vector<Piece*> getPieces();

private:

	void createGrid(sf::Vector2u t_windowSize);
	void connectTiles();
	void generateCosts();
	void createPieces();

	std::vector<Tile*> m_grid;
	std::vector<Piece*> m_pieces;

	std::array<Tile*, 2> m_furthestGoalTiles;

	const float m_TILE_RADIUS{ 10.0f };;
	const int m_MAX_ROW_LENGTH{ 13 };
};

