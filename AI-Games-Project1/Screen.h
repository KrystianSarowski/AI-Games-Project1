#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "enum.h"

/// @brief Enum class for Opponents.
/// 
/// Keeps track of what opponent the player is against.
enum class GameplayStates
{
	PlayerVsAi,
	AiVsAi,
	PlayerVsPlayer
};

/// @brief Enum class for Diffuculty of AI.
/// 
/// Changes the depth of the MinMax Algorithm.
enum class Difficulty
{
	Easy,
	Normal
};


class Screen
{
public:

	/// @brief Constructor of Screen.
	/// 
	/// It calls the initialise() function. Assigns m_gameScreen to the passed in reference.
	/// @see GameScreen.
	/// @param t_gameScreen This is a reference to the enum varaible of current screen. 
	Screen(GameScreen &t_gameScreen);

	/// @brief Virtual function that updates the screen.
	/// 
	/// @param t_dt This is the delta time.
	virtual void update(sf::Time t_dt);

	/// @brief Virtual Render Function.
	/// 
	///@param t_window The render window. This is passed by reference.
	virtual void render(sf::RenderWindow& t_window);

	/// @brief Proccess Events within the current screen.
	/// 
	/// @param t_event The event that is used in this screen.
	/// @param t_pos The current position of the mouse cursor.
	virtual void processEvents(sf::Event& t_event, sf::Vector2f t_pos);

	/// <summary>
	/// Called when the screen starts up
	/// </summary>
	virtual void start();

protected:
	/// <summary>
	/// Static Instance of the enum class GameplayStates
	/// </summary>
	static GameplayStates s_gameplayState;
	
	/// <summary>
	/// Static instance of the enum class Difficulty
	/// </summary>
	static Difficulty s_difficulty;

	/// <summary>
	/// Instance of GameScreen
	/// </summary>
	GameScreen &m_gameScreen;
	
	/// <summary>
	/// sf::texture of m_hud, The background of the screen
	/// </summary>
	sf::Texture m_texture;

	/// <summary>
	/// Sprite of the background image
	/// </summary>
	sf::Sprite m_hud;

	/// <summary>
	/// font that the sf::Text uses
	/// </summary>
	sf::Font m_font;

	/// <summary>
	/// Position of the Screen
	/// </summary>
	sf::Vector2f m_postion{ 0.0f,0.0f};

	/// <summary>
	/// Instance of enum class AnimationMode
	/// </summary>
	AnimationMode m_animationState{ AnimationMode::Appear };

	/// @brief Initialses font
	/// 
	/// Loads in the font
	virtual void initialise();

	/// <summary>
	/// Assigns m_position to the passed in vector
	/// </summary>
	/// @param t_position Vector that will be assigned to m_position
	virtual void setPosition(sf::Vector2f t_postion);
};