#pragma once
#include "Piece.h"

class Player
{
public:

	/// @brief Constructor for the Player.
	/// 
	/// Constructor for the Player that sets all the passed in variables to corrsponding
	/// memeber variables.
	/// @param t_pieceType the PieceType that Player controls.
	/// @param t_name the name of the Player.
	/// @see PieceType
	Player(PieceType t_pieceType, std::string t_name);

	/// @brief Sets the m_madeMove to the passed in bool.
	/// 
	/// Sets the m_madeMove to the passed in bool
	/// @param t_madeMove the bool to which m_madeMove will be set to.
	void setMadeMove(bool t_madeMove);

	/// @brief Sets the m_controlledByAI to the passed in bool.
	/// 
	/// Sets the m_controlledByAI to the passed in bool
	/// @param t_isControlledByAI the bool to which m_controlledByAI will be set to.
	void setControlledByAI(bool t_isControlledByAI);

	/// @brief Adds the Piece to the list of pieces that the Player controls.
	/// 
	/// Adds the Piece to the list of pieces that the Player controls.
	/// @param t_piece the pointer to the Piece that is to be added to the list of pieces.
	void addPiece(Piece* t_piece);

	/// @brief Moves the passed in Piece from the current Tile it is occupying to the passed in Tile.
	/// 
	/// Moves the passed in Piece from the current Tile it is occupying to the passed in Tile.
	/// @param t_pieceToMove the pointer to the Piece that is to be moved.
	/// @param t_destTile the pointer to the Tile that the Piece is to be moved to.
	void makeAMove(Piece* t_pieceToMove, Tile* t_destTile);

	/// @brief Process the Tile has been passed to make a move.
	/// 
	/// Checks if the passed in Tile contains the m_selectedPiece to deslect.
	/// Checks if the m_moveTiles contains the passed in Tile.
	/// Checks if the passed in Tile contains a Piece that the player controls.
	/// And based on the list condition it acts accordingly.
	/// @param t_selectedTile the tile that has been selected.
	/// @see makeAMove(Piece* t_pieceToMove, Tile* t_destTile), clearSelection()
	void processTile(Tile* t_selectedTile);

	/// @brief Draws all the possible moves that the Player can mae on screen.
	/// 
	/// Draws a circle marker on the position of each of the m_moveTiles within
	/// the passed in render window.
	/// @param t_window The window in which each marker will be draw in.
	void render(sf::RenderWindow& t_window);

	/// @brief Clears the m_selectedPiece and m_moveTiles.
	/// 
	/// Clears the m_selectedPiece and m_moveTiles to default values.
	void clearSelection();

	/// @brief Gets the bool for if the Player has finished their turn.
	/// 
	/// Gets the bool for if the Player has finished their turn.
	/// @return a bool for if the Player has made a move.
	/// @see makeAMove(Piece* t_pieceToMove, Tile* t_destTile)
	bool getMadeMove();

	/// @brief Gets the bool for if the Player has is controled by an Algorithm.
	/// 
	/// Gets the bool for if the Player has is controled by an Algorithm.
	/// @return a bool for if the Player is controled by an Algorithm.
	/// @see Algorithm
	bool getControlledByAI();

	/// @brief Gets the PieceType that the Player controls.
	/// 
	/// Gets the PieceType that the Player controls.
	/// @return enum for the PieceType that the Player controls.
	/// @see PieceType
	PieceType getOwnedPieceType();
	
	/// @brief Gets the name of the Player.
	/// 
	/// Gets the name of the Player.
	/// @return a string for the name of the Player.
	std::string getPlayerName();

	/// @brief Gets a vector all the pieces that the Player controls.
	/// 
	/// Gets a vector all the pieces that the Player controls.
	/// @return A vector all the pieces that the Player controls.
	std::vector<Piece*> getPieces();

	/// @brief Gets a list all the tiles that the Player can move to current select Piece.
	/// 
	/// Gets a list all the tiles that the Player can move to current select Piece.
	/// @return A list all the tiles that the Player can move to current select Piece.
	std::list<Tile*> getMoveList();

private:

	/// @brief Name of the Player.
	/// 
	/// Name of the Player.
	std::string m_name;

	/// @brief The PieceType that the Player controls.
	/// 
	/// The PieceType that the Player controls.
	/// @see PieceType
	PieceType m_ownedType;

	/// @brief A vector all the pieces that the Player controls.
	/// 
	/// A vector all the pieces that the Player controls.
	/// @see Piece
	std::vector<Piece*> m_pieces;

	/// @brief A list all the tiles that the Player can move to current select Piece.
	/// 
	/// A list all the tiles that the Player can move to current select Piece.
	/// @see Tile
	std::list<Tile*> m_moveTiles;

	/// @brief A pointer to the Piece that the Player is trying to move.
	/// 
	/// A pointer to the Piece that the Player is trying to move.
	/// @see Piece
	Piece* m_selectedPiece;

	/// @brief A bool for if the Player has made a move this turn.
	/// 
	/// A bool for if the Player has made a move this turn.
	bool m_madeMove{ false };

	/// @brief A bool for if the Player is controlled by Algorithm.
	/// 
	/// A bool for if the Player is controlled by Algorithm.
	bool m_controlledByAI{ false };
};