#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"
class OpponentScreen : public Screen
{
public: 
	OpponentScreen(GameScreen& gamescreen);
	void update(sf::Time t_dt);
	void render(sf::RenderWindow& t_window);
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);

private:
	void initialise();
	void setupButtons();
	void setupText();

	sf::RectangleShape m_pvcButton;
	sf::RectangleShape m_cvcButton;
	sf::RectangleShape m_pvpButton;

	sf::Text m_pvcText;
	sf::Text m_cvcText;
	sf::Text m_pvpText;

};

