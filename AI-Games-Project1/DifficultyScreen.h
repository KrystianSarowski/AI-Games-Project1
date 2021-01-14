#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"

class DifficultyScreen : public Screen
{
public:
	DifficultyScreen(GameScreen& gamescreen);
	void update(sf::Time t_dt);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);
	void start(GameScreen t_previousState);
	void end();

private:
	void initialise();
	void setupButtons();
	void setupText();

	sf::RectangleShape m_eButton;
	sf::RectangleShape m_mButton;
	sf::RectangleShape m_hButton;

	sf::Text m_eText;
	sf::Text m_mText;
	sf::Text m_hText;

};