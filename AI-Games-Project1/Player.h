#pragma once
#include "Piece.h"

class Player
{
public:

	Player(PieceType t_pieceType, std::string t_name);

	void setMadeMove(bool t_madeMove);
	void setControlledByAI(bool t_isControlledByAI);
	void addPiece(Piece* t_piece);
	void makeAMove(Piece* t_pieceToMove, Tile* t_destTile);
	void processTile(Tile* t_selectedTile);
	void render(sf::RenderWindow& t_window);
	void clearSelection();
	
	bool getMadeMove();
	bool getControlledByAI();

	PieceType getOwnedPieceType();

	std::string getPlayerName();
	std::vector<Piece*> getPieces();
	std::list<Tile*> getMoveList();

private:

	std::string m_name;
	PieceType m_ownedType;

	std::vector<Piece*> m_pieces;
	std::list<Tile*> m_moveTiles;

	Piece* m_selectedPiece;

	bool m_madeMove{ false };
	bool m_controlledByAI{ false };
};