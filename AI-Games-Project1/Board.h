#pragma once
#include "Tile.h"
#include "Piece.h"
#include "MyMath.h"
#include <array>
#include <queue>

class Board
{
public:

	/// @brief Constructor of the Board.
	/// 
	/// Calls various function to create all instances of Tile and connect them with each other
	/// and then create the pieces for each side of the board.
	/// @param t_windoSize the size of the window in which the board will be placed. 
	Board(sf::Vector2u t_windoSize);

	/// @brief Gets the pointer to the Tile that contains the passed in position.
	/// 
	/// Tries to find and return the pointer to the Tile that contains the passed in position. 
	/// If there is no Tile found that contains the position it returns nullptr.
	/// @param t_mousePos the position within the game world for which a Tile is searched.
	/// @return a pointer to the Tile that contains the passed in position.
	Tile* selectTile(sf::Vector2f t_mousePos);

	/// @brief Draws all the tiles on screen.
	/// 
	/// Creates a fake tile circle shape that it draws in every tile position.
	/// It then calls the Piece::render(sf::RenderWindow& t_window) to draw itself.
	/// @param t_window reference to the window in which everything will be drawn.
	void render(sf::RenderWindow& t_window);

	/// @brief Gets all the pieces of the passed in PieceType in a vector.
	/// 
	/// Gets all the pieces of the passed in PieceType in a vector by converting 
	/// the PieceType to integer and indexing into m_pieces.
	/// @param t_type the PieceType of the pieces to return.
	/// @return a vector of all the pieces of the passed in PieceType.
	std::vector<Piece*> getPieces(PieceType t_type);

	/// @brief Calculates the value of advantage over the other player.
	/// 
	/// Calculates the value of each Piece position of a certain PieceType
	/// varsus the position of the other pieces. If the number is a negative
	/// the opponent has an advantage otherwise the player controlling the passed
	/// in PieceType has an advantage.
	/// @param t_type the PieceType of the player for who we are checking the advantage.
	/// @return the value of the advantage either positive or negative.
	int calculateValue(PieceType t_type);

	/// @brief A bool for if the passed in PieceType has won.
	/// 
	/// Checks if all the pieces of the passed in PieceType are in the opposing player's
	/// starting locations if yes that player has won then.
	/// @param t_type the PieceType of the player for who we are checking if the won.
	/// @return bool for if all the opposing PieceType tiles are occupied by the passed in PieceType.
	bool checkForWin(PieceType t_type);

	/// @brief Resets the position of all pieces in the Board to the starting positions.
	/// 
	/// Sets all the pieces contained in Board to null Tile and then moves them to
	/// the starting tiles.
	void restart();

private:

	/// @brief Creates a grid of tiles using to triangular patterns.
	/// 
	/// Creates a grid of tiles using the a pattern of two triangles. The second triangle
	/// is flipped upsided down and every Tile that overlapse the created tiles is deleted.
	/// The top 10 and bottom 10 tiles as set as the goal tiles for each PieceType.
	/// The starting position of each triangle is such that the pattern is centred with the passed
	/// in size. At the end it calls the function to connect the tiles and setup the goal costs to
	/// the furthest goal tiles (the very top and the very bottom).
	/// @param t_windowSize the size of the windown in which the gird will be centered.
	/// @see connectTiles(), generateDistanceCosts(std::vector<Tile*> t_furthestGoalTiles)
	void createGrid(sf::Vector2u t_windowSize);

	/// @brief Connects each tile with it's adjecant neighbours.
	/// 
	/// Connects each tile within the grid with all the tiles that are with a certain deistance.
	/// @see createGrid(sf::Vector2u t_windowSize)
	void connectTiles();

	/// @brief Generates the cost from each tile to each of the furthest goals.
	/// 
	/// Generates the distance cost from each Tile to the each of the furthest goal
	/// tiles that are passed into this function.
	/// @param t_furthestGoalTiles a vector that contains the pointest to the furthest goal tiles.
	/// @see createGrid(sf::Vector2u t_windowSize)
	void generateDistanceCosts(std::vector<Tile*> t_furthestGoalTiles);

	/// @brief Creates a Piece within each of the Tile in the m_goalTiles vectors.
	/// 
	/// Creates a pointer to a Piece for each Tile within the m_goalTiles vectors setting 
	/// it PieceType by converting the index used to traves the vector.
	void createPieces();

	/// @brief Vector of all Tile pointers that make up the Board.
	/// 
	/// Vector that contains all the Tile pointers that are within the Board and
	/// are inter connected with one another.
	/// @see Tile
	std::vector<Tile*> m_grid;

	/// @brief Vector of vectors that contains pointer to each of the goal tiles.
	/// 
	/// Vector of vectors that contains within each vector goal tiles for each of
	/// the PieceTypes. The index used to traves is the same as the index of each PieceType.
	/// @see Tile, PieceType
	std::vector<std::vector<Tile*>> m_goalTiles;

	/// @brief Vector of vectors that contains pointer to each of the pieces.
	/// 
	/// Vector of vectors that contains within each vector pieces for each of
	/// the PieceTypes. The index used to traves is the same as the index of each PieceType.
	/// @see Tile, PieceType
	std::vector<std::vector<Piece*>> m_pieces;

	/// @brief The radius of the Tile.
	/// 
	/// The radius of the Tile used for calucaltion and rendering.
	const float m_TILE_RADIUS{ 15.0f };

	/// @brief The number of tiles within the largest row with the triangle grids.
	/// 
	/// The number of tiles within the largest row with the triangle grids. This
	/// is only used when making of the grid.
	/// @see createGrid(sf::Vector2u t_windowSize)
	const int m_MAX_ROW_LENGTH{ 13 };

};