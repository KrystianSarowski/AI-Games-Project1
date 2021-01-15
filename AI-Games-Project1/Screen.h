#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "enum.h"

enum class GameplayStates
{
	PlayerVsAi,
	AiVsAi,
	PlayerVsPlayer
};

enum class Difficulty
{
	Easy,
	Normal
};

class Screen
{
public:

	Screen(GameScreen &t_gamescreen);
	virtual void update(sf::Time t_dt);
	virtual void render(sf::RenderWindow& t_window);
	virtual void processEvents(sf::Event& t_event, sf::Vector2f t_pos);
	virtual void start();

protected:
	
	static GameplayStates s_gameplayState;
	
	static Difficulty s_difficulty;

	GameScreen &m_gameScreen;
	
	sf::Texture m_texture;

	sf::Sprite m_hud;

	sf::Font m_font;

	sf::Vector2f m_postion{ 0.0f,0.0f};

	AnimationMode m_animationState{ AnimationMode::Appear };

	virtual void initialise();
	virtual void setPosition(sf::Vector2f t_postion);
};