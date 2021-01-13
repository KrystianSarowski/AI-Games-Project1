#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"
#include "Algorithm.h"
#include "Board.h"

class Gameplay : public Screen
{
public:

	Gameplay(GameScreen& gamescreen);
	void update(sf::Time t_dt);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);
	void start(GameScreen t_previousState);
	void end();
	void addPiecesToPlayers();
private:
	void initialise();
	int m_currentTurn = 0;
	Board m_board;
	Player* m_players[2];
	Algorithm* m_ai;
	Algorithm* m_theCoolerAI;
	sf::Sprite m_boardSprite;
	sf::Texture m_boardTexture;
	bool isGameWon = false;

	sf::Text m_gameoverText;
	sf::RectangleShape m_gameoverHud;
	sf::RectangleShape m_returnButton;
	sf::Text m_returnText;
};

