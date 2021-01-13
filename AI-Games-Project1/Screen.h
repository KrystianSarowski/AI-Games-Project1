#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "enum.h"
static enum class GameplayStates
{
	PlayerVsAi,
	AiVsAi,
	PlayerVsPlayer
};

static enum class Difficulty
{
	Easy,
	Medium,
	Hard
};

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
	GameplayStates m_gameplayState;
	Difficulty m_difficulty;
	sf::Sprite m_hud;

	sf::Font m_font;

	sf::Vector2f m_postion{ 0.0f,0.0f};

	AnimationMode m_animationState{ AnimationMode::Appear };

	virtual void initialise();
	virtual void setPosition(sf::Vector2f t_postion);
};

