#pragma once
#include "Tile.h"
#include <array>
#include <queue>
#include "Player.h"

class Game
{
public:

	Game();
	void start();
	std::vector<Tile*> m_grid;
	std::array<Tile*, 2> m_goalTiles;
	sf::VertexArray m_points{ sf::Lines, 2 };

private:

	void update(sf::Time dt);
	void createTileGrid(float t_tileRadius, int t_maxRowLength);
	void connectTiles(float t_tileRadius);
	void generateGoalCost(int t_goalIndex);
	Tile* findSelectedTile(sf::Vector2f t_pos);
	float distance(sf::Vector2f t_vect1, sf::Vector2f t_vect2);
	void processEvents();
	void render();

	Player* m_player;

	sf::RenderWindow m_window;
};

