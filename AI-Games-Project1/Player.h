#pragma once
#include "Piece.h"


class Player
{
public:

	Player(PieceType t_pieceType);

	void addPiece(Piece* t_piece);
	void setMadeMove(bool t_madeMove);
	void processSelectedTile(Tile* t_selectedTile);
	void render(sf::RenderWindow& t_window);
	bool getMadeMove();

private:

	PieceType m_ownedType;

	std::list<Piece*> m_pieces;
	std::list<Tile* > m_moveTiles;

	Piece* m_selectedPiece;

	bool m_madeMove = false;
};

