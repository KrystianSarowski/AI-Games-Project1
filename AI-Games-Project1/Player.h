#pragma once
#include "Piece.h"


class Player
{
public:

	Player(PieceType t_pieceType);

	void addPiece(Piece* t_piece);
	void makeAMove(Piece* t_pieceToMove, Tile* t_destTile);
	void setMadeMove(bool t_madeMove);
	void processTile(Tile* t_selectedTile);
	void render(sf::RenderWindow& t_window);
	void clearSelection();
	
	bool getMadeMove();

	std::vector<Piece*> getPieces();
	std::list<Tile*> getMoveList();

	PieceType m_ownedType;

private:

	std::vector<Piece*> m_pieces;
	std::list<Tile*> m_moveTiles;

	Piece* m_selectedPiece;

	bool m_madeMove = false;
};

