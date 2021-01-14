#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainScreen.h"
#include "OpponentScreen.h"
#include "DifficultyScreen.h"
#include "Gameplay.h"

class Game
{
public:

	Game();
	void start();

private:

	void update(sf::Time dt);
	void processEvents();
	void render();
	sf::Music m_bgMusic;
	sf::RenderWindow m_window;
	std::vector<Screen*> m_screens;
	GameScreen m_currentState;
	GameScreen m_previousState;
};

