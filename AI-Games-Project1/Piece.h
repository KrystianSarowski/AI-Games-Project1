#pragma once
#include "Tile.h"

/// @brief The type of Colour that a Piece or Tile is.
/// 
/// Enum used to index into various function to get the pieces and tiles
/// of the same colour type. The player also uses to know what colour they control.
/// @see Player, Tile, Piece
enum class PieceType
{
	RED,
	GREEN
};

class Piece
{
public:

	/// @brief The default constructor for Piece.
	/// 
	/// The default constructor for Piece which creates the m_body of the Piece.
	Piece();

	/// @brief The radius of the Piece.
	/// 
	/// The radius of the Piece that is used to set the size of m_body.
	static float s_radius;

	/// @brief Set the PieceType that this Piece is.
	/// 
	/// Sets the PieceType ie the type of colour this Piece is.
	/// @param t_type the PieceType of this Piece.
	/// @see PieceType
	void setType(PieceType t_type);

	/// @brief Sets the Tile that this Piece occupies.
	/// 
	/// Sets the Tile that this Piece occupies by setting the passed in Tile to occupied. 
	/// If the passed in pointer is nullptr it does not change the Tile to occupied.
	/// @param t_newTile the pointer to the new Tile that the Piece will occupy.
	/// @see Tile
	void setTile(Tile* t_newTile);

	/// @brief Draws the m_body of the Piece in the passed in window.
	/// 
	/// Draws the circle shaped called m_body in the passed window.
	/// @param t_window reference to the window in hwich the Piece will be drawn in.
	void render(sf::RenderWindow& t_window);
	
	/// @brief Gets the pointet to the Tile the Piece occupies.
	/// 
	/// Gets the pointer to the Tile the Piece occupies.
	/// @return the pointer to the TIle that this Piece occupies.
	Tile* getTile();

	/// @brief Gets the PieceType of this Piece.
	/// 
	/// Gets the PieceType of this Piece.
	/// @return the PieceType of this Piece.
	PieceType getType();

	/// @brief Gets all the possible tiles that the Piece can move to.
	/// 
	/// Gets a list of of pointers to all the tiles that this Piece can move to.
	/// It calls getJumpOverMoves(std::list<Tile*>& t_moveList, Tile* t_tile) in order
	/// to check if it can jump over adjecent pieces.
	/// @return a list of pointers to the tiles that this Piece can move to.
	std::list<Tile*> getPossibleMoves();

	/// @brief Gets all the tiles the Piece can jump over to.
	/// 
	/// This function calls itself recursivly to check if the Piece
	/// can jump over a Piece to an empty Tile. Each time it succeds it calls itself on
	/// that tile and add that Tile to the list of possible moves.
	/// @param t_moveList refernece to the list of tiles that Piece can move to.
	/// @param t_tile pointer to the Tile that we are checking if we can jump over from.
	void getJumpOverMoves(std::list<Tile*>& t_moveList, Tile* t_tile);

private:

	/// @brief The PieceType of this Tile.
	/// 
	/// The PieceType of this Tile.
	PieceType m_type;

	/// @brief Pointer to the Tile that the Piece is occupying.
	/// 
	/// Pointer to the Tile that the Piece is occupying.
	Tile* m_tile;

	/// @brief The circle shape that is used for the body of the Piece.
	/// 
	/// The circle shape that is used for the body of the Piece.
	sf::CircleShape m_body;
};

