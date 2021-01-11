#pragma once
#include "Board.h"
#include "PlayerAI.h"

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
	PlayerAI* m_playerAI;

	int m_currentTurn = 0;

	sf::RenderWindow m_window;
};

