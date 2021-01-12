#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"
class MainScreen : public Screen
{
public:
	MainScreen(GameScreen& t_gamescreen);
	void update(sf::Time t_dt);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);
	void start(GameScreen t_previousState);
	void end();
	
private:
	void initialise();
	void setupButtons();
	void setupText();
	sf::RectangleShape m_playButton;
	sf::RectangleShape m_quitButton;

	sf::Text m_playText;
	sf::Text m_quitText;

};

