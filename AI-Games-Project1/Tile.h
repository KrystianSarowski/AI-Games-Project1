#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <array>
#include <math.h>

/// This is the Tile Class.
/// 
/// Fragment of the board where the pieces can traverse .
class Tile
{
public:
	/// @brief Contructor of the tile class.
	/// 
	/// Initialises m_occupied to false, m_position to zero and the distances to goal to -1.
	Tile();

	/// @brief Sets position of the Tile.
	/// 
	/// Assigns m_position to the passed in vector.
	/// @param t_pos The position the Tile is assigned to 
	void setPosition(sf::Vector2f t_pos);

	/// @brief Sets if the Tile is occupied or not. 
	/// 
	/// Assigns m_isOccupied to the passed in bool
	/// @param t_isOccupied If the Tile is occupied or not
	void setIsOccupied(bool t_isOccupied);

	/// @brief Adds neighbour tiles into a List of Tiles
	/// 
	/// 
	/// @param t_neighbour A pointer to a neighbour Tile
	void addNeighbour(Tile* t_neighbour);

	/// @brief Sets the distance to the goal
	/// 
	/// @param t_index The index in the array
	/// @param t_cost The compination of veritical distance and distance
	void setDistanceToGoal(int t_index, int t_cost);

	///	@brief Sets the vertical distance to the goal
	/// 
	/// 
	/// @param t_index The index in the array
	/// @param t_cost The compination of veritical distance and distance
	void setVerticalDistanctToGoal(int t_index, int t_cost);

	/// @brief Gets the list of neighbours from this tile
	/// 
	/// 
	/// @return A list of pointer Tile neighbours
	std::list<Tile*> getNeighbours() const;

	/// @brief Gets the current position of this Tile
	/// 
	/// 
	/// @return A vector of the position of this Tile
	sf::Vector2f getPosition() const;

	/// @brief Gets the Neighbour Tile thats in the passed in vector
	/// 
	/// @param t_direction A vector to the neighbour tile
	/// @return A pointer to a Tile from the direction of t_direction
	Tile* getNeighbourInDirection(sf::Vector2f t_direction) const;

	/// @brief Checks if the Tile is occupied or not
	/// 
	/// 
	/// @return A bool if the tile is occupied or not
	bool getIsOccupied() const;

	/// @brief Returns the sum of vertical distance to the goal and the normal distance
	/// 
	///
	/// @param t_index The index in the array
	/// @return The combination of Vertical distance to the goal and the normal distance
	int getTotalGoalCost(int t_index) const;

private:

	/// <summary>
	/// Position of the Tile
	/// </summary>
	sf::Vector2f m_position;

	/// <summary>
	/// List of pointer Tiles
	/// </summary>
	std::list<Tile*> m_neighbours;

	/// <summary>
	/// bool if Tile is Occupied or not
	/// </summary>
	bool m_isOccupied;

	/// <summary>
	/// array of type int, distance to its corresponsing goal
	/// </summary>
	std::array<int, 2> m_distanceToGoals;

	/// <summary>
	/// array of type int, vertical distance to its corresponsing goal
	/// </summary>
	std::array<int, 2> m_verticalDistanceToGoals;
};