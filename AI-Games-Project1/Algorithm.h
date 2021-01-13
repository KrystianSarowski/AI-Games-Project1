#pragma once
#include "Player.h"
#include "Board.h"
#include <limits>

struct Evaluation
{
	Evaluation() = default;

	Tile* m_targetTile = nullptr;
	Piece* m_piece = nullptr;

	int m_alphaPruning = INT_MIN;
	int m_betaPruning = INT_MAX;
};


class Algorithm 
{
public:

	Algorithm(Player* t_player, Board* t_board);

	int miniMax(Evaluation& t_evaluation, int t_typeIndex, int t_depth, bool t_maximizing);
	
	void calculateMove();
	void makeMove(sf::Time t_dt);

private:

	sf::Time m_moveDelay;

	float m_delayTime = 0.5f;

	bool m_moveCalculated;

	Player* m_player;
	Board* m_board;

	Evaluation m_moveEvaluation;

	void simulateMove(Piece* t_piece, Tile* t_tile);
	std::vector<std::list<Tile*>> getPossibleMoves(PieceType t_type);
};

