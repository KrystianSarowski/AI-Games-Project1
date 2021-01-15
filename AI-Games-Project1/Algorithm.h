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

	void makeMove(sf::Time t_dt);
	void reset();

	static void setPredictionDepth(int t_depth);

private:

	static int s_predictionDepth;

	sf::Time m_moveDelay{ sf::seconds(0.0f) };;

	float m_delayTime{ 0.5f };

	bool m_moveCalculated{ false };

	Player* m_player;
	Board* m_board;

	Evaluation m_moveEvaluation;

	void calculateMove();
	void simulateMove(Piece* t_piece, Tile* t_tile);

	int miniMax(Evaluation& t_evaluation, int t_typeIndex, int t_depth, bool t_maximizing);

	std::vector<std::list<Tile*>> getPossibleMoves(PieceType t_type);
};

