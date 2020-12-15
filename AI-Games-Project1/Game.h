#pragma once
#include "Tile.h"

class Game
{
public:

	Game();
	void start();
	std::vector<Tile*> m_grid;
	sf::VertexArray m_points{ sf::Lines, 2 };

private:

	void update(sf::Time dt);
	void createTileGrid(float t_tileRadius, int t_maxRowLength);
	void connectTiles(float t_tileRadius);
	float distance(sf::Vector2f t_vect1, sf::Vector2f t_vect2);
	void processEvents();
	void render();

	sf::RenderWindow m_window;
};

