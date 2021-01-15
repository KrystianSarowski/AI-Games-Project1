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

	/// @brief Constructor of the Algorithm class. 
	/// 
	/// Sets the pointer to the Algorithm::m_player for the Player that the algorithm controls and sets the
	/// the pointer to Algorithm::m_board for the Board on which the AI makes moves.
	/// @param t_player The pointer to the Player to which Algorithm::m_player will be set to.
	/// @param t_board The pointer to the Board to which Algorithm::m_board will be set to.
	Algorithm(Player* t_player, Board* t_board);

	/// @brief Makes a move for the player its controlling using the evaluation from MiniMax.
	/// 
	/// Calls the function calculateMove() to make the move for the controlled player.
	/// After the calcualteMove() finishes the function waits until sufficente enough time
	/// has passed and move's the piece to target location ending its turn using Player::processTile(Tile* t_selectedTile).
	/// @see calculateMove(), Player::processTile(Tile* t_selectedTile)
	/// @param t_dt The time that has passed since last update. 
	void makeMove(sf::Time t_dt);

	/// @brief Resets all the important variables to default state.
	/// 
	/// Sets m_moveCalculated to false so the next makeMove() will start from scratch.
	void reset();

	/// @brief Set the static variable s_predictionDepth.
	/// 
	/// Sets the s_predictionDepth to the passed in variable that is used in calculateMove() to kickoff MiniMax.
	/// @see calculateMove() 
	/// @param t_depth The value to which s_predictionDepth will be set to. 
	static void setPredictionDepth(int t_depth);

private:

	/// @brief Integer for initital depth that all instances Algorithm use to start MiniMax
	/// 
	/// This int is used as the start value for MiniMax in the calculateMove()
	/// @see calculateMove()
	static int s_predictionDepth;

	/// @brief Float for the time delay.
	/// 
	/// The time delay before the second part of makeMove(sf::Time t_dt)
	/// @see makeMove(sf::Time t_dt)
	float m_delayTime{ 0.5f };

	/// @brief Bool for if the Algorithm has already calcualted the move for this turn.
	/// 
	/// Bool used to check if Algorithm has already ran the calculateMove() function 
	/// this turn.
	/// @see calculateMove()
	bool m_moveCalculated{ false };

	/// @brief A pointer to instance of Player that this Algorithm controles.
	/// 
	/// A pointer to the instance of Player that the Algorithm uses to check which
	/// which pieces to move for the instace of Player.
	/// @see Player
	Player* m_player;

	/// @brief A pointer to the instance of Board in Gameplay
	/// 
	/// A pointer to the instance of Board that the Algorithm get the pieces
	/// that the MiniMax can move.
	/// @see Board
	Board* m_board;

	/// @brief Evaluation struct that stores the best move from MiniMax.
	/// 
	/// Evaluation from the MiniMax that containts the Piece that is to
	/// be moved and the Tile to which the Piece will be moved to.
	/// @see makeMove(sf::Time t_dt), miniMax(Evaluation& t_evaluation, int t_typeIndex, int t_depth, bool t_maximizing)
	Evaluation m_moveEvaluation;

	/// @brief Delay before the Algorithm finishes it's move.
	/// 
	/// The time delay before the rest of the makeMove(sf::Time t_dt) function
	/// finishes by moveing the select Piece to target Tile in Player::processTile(Tile* t_selectedTile).
	/// @see makeMove(sf::Time t_dt), Player::processTile(Tile* t_selectedTile)
	sf::Time m_moveDelay{ sf::seconds(0.0f) };

	/// @brief Starts the MiniMax function and select the Piece with Evaluation.
	/// 
	/// Sets the pruning alpha to minmum value and sets the pruning beta to maximum with the
	/// Evaluation and starts the MiniMax function. After MiniMax finishes it sets m_moveCalculated
	/// to true and calls Player::processTile(Tile* t_selectedTile) to select the Piece from Evaluation.
	/// @see miniMax(Evaluation& t_evaluation, int t_typeIndex, int t_depth, bool t_maximizing), Player::processTile(Tile* t_selectedTile)
	void calculateMove();

	/// @brief Force moves the passed in Piece to the passed in Tile.
	/// 
	/// Used by the MiniMax to simulate the movement that either Player could
	/// do with a Piece they control. It moves the Piece from the current Tile
	/// to the passed in target Tile.
	/// @param t_piece pointer to the Piece that is to be moved.
	/// @param t_tile pointer to the Tile that the Piece is to be moved to.
	/// @see miniMax(Evaluation& t_evaluation, int t_typeIndex, int t_depth, bool t_maximizing)
	void simulateMove(Piece* t_piece, Tile* t_tile);

	/// @brief Does the MiniMax algorithm by calling itself recursavly.
	/// 
	/// Does the MiniMax algorthim by calling itself recursavly until it reaches
	/// the depth of 0 or sees that either Player has won. Whever it it trying to maximize
	/// it does the first if statment other wise it does the else bit. With each iteration
	/// of the MiniMax function it tries to cut down the calcuations by checking the pruning values
	/// with the passed in Evaluation. Each time MiniMax simulates the movement of the Piece and moves
	/// simulates it back before ending itself.
	/// @param t_evaluation refrence to the Evaluation that carries the move that has been made and pruning values.
	/// @param t_typeIndex the integer value for the PieceType.
	/// @param t_depth the integer value for how many more times the MiniMax needs to call itself.
	/// @param t_maximizing bool for if this iteration of MiniMax is looking for the biggest value.
	/// @return The value of the MiniMax calculations.
	/// @see simulateMove(Piece* t_piece, Tile* t_tile)
	int miniMax(Evaluation& t_evaluation, int t_typeIndex, int t_depth, bool t_maximizing);

	/// @brief Gets all the possible moves for all the pieces of the same PieceType
	/// 
	/// Creates a vector of with a list of all the possible moves the a Piece can do
	/// for all the pieces of the passed in PieceType
	/// @param t_type PieceType for which we want to get all possible moves.
	/// @return a vector of lists of all the possible tiles a Piece can move into
	std::vector<std::list<Tile*>> getPossibleMoves(PieceType t_type);
};

