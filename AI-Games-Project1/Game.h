#pragma once
#include "Board.h"
#include "Algorithm.h"

class Game
{
public:

	Game();
	void start();

private:

	void update(sf::Time dt);
	void processEvents();
	void render();
	void addPiecesToPlayers();

	Board m_board;
	Player* m_players[2];
	Algorithm* m_ai;
	Algorithm* m_theCoolerAI;

	int m_currentTurn = 0;

	sf::RenderWindow m_window;
};

