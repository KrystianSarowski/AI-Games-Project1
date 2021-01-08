#pragma once
#include "Tile.h"

enum class PieceType
{
	RED,
	GREEN
};

class Piece
{
public:

	Piece(PieceType t_type);

	static float s_radius;

	void changeTile(Tile* t_newTile);
	void render(sf::RenderWindow& t_window);
	Tile* getTile();

	std::list<Tile*> getPossibleMoves();

	void jumpOver(std::list<Tile*>& t_moveList, Tile* t_tile);

private:

	PieceType m_type;

	Tile* m_tile;

	sf::CircleShape m_body;
};

