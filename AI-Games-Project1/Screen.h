#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "enum.h"
class Screen
{
public:
	Screen(GameScreen &t_gamescreen);
	virtual void update(sf::Time t_dt);
	virtual void render(sf::RenderWindow& t_window);
	virtual void processEvents(sf::Event& t_event, sf::Vector2f t_pos);
	virtual void start(GameScreen t_previousState);
	virtual void end();
protected:
	GameScreen & m_gamescreen;
	sf::Texture m_texture;

	sf::Sprite m_hud;

	sf::Font m_font;

	sf::Vector2f m_postion{ 0.0f,0.0f};

	AnimationMode m_animationState{ AnimationMode::Appear };

	virtual void initialise();
	virtual void setPosition(sf::Vector2f t_postion);
};

