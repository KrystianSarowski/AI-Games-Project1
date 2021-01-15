#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MainScreen.h"
#include "OpponentScreen.h"
#include "DifficultyScreen.h"
#include "Gameplay.h"

class Game
{
public:

	/// @brief Default constructor for Game
	/// 
	/// The dafault constructor for Game, sets the previous
	/// and current GameScreen to the Main screen.
	Game();

	/// @brief Starts the main game loop that runs until the screen closed.
	/// 
	/// Runs the main game loop until the m_window is closed down.
	void start();

private:

	/// @brief Updates once per 1/60 th of a second.
	/// 
	/// Updates once per 1/60 th of a second.
	/// @param dt time since the last update.
	void update(sf::Time dt);

	/// @brief Procces all the events that have occured within the m_window.
	/// 
	/// Procces all the events that have occured within the m_window.
	void processEvents();

	/// @brief Calls all the render functions to draw what is happening in m_window.
	/// 
	/// Calls all the render functions to draw what is happening in m_window.
	void render();
	
	/// @brief The background music of the Game.
	/// 
	/// The background music of the Game.
	sf::Music m_bgMusic;

	/// @brief The window in which all events occur and all sprites are drawn.
	/// 
	/// The window in which all events occur and all sprites are drawn.
	sf::RenderWindow m_window;

	/// @brief Vector of all the screens that exist in Game.
	/// 
	/// Vector of all the screens that exist in Game.
	std::vector<Screen*> m_screens;
	
	/// @brief The GameScreen that the Game is currently in.
	/// 
	///  The GameScreen that the Game is currently in.
	GameScreen m_currentState;

	/// @brief The GameScreen that the Game was in last update.
	/// 
	/// The GameScreen that the Game was in last update.
	GameScreen m_previousState;
};

