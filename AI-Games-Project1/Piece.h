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

	Piece();

	static float s_radius;

	void setType(PieceType t_type);
	void setTile(Tile* t_newTile);

	void render(sf::RenderWindow& t_window);
	
	Tile* getTile();
	PieceType getType();

	std::list<Tile*> getPossibleMoves();

	void getJumpOverMoves(std::list<Tile*>& t_moveList, Tile* t_tile);

private:

	PieceType m_type;

	Tile* m_tile;

	sf::CircleShape m_body;
};

