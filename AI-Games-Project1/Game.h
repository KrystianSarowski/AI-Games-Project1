#pragma once
#include <SFML/Graphics.hpp>

class Game
{
public:

	Game();
	void start();

private:

	void update(sf::Time dt);
	void processEvents();
	void render();

	sf::RenderWindow m_window;
};

