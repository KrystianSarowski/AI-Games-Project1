#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"

class OpponentScreen : public Screen
{
public: 
	/// @brief Constructor of the OpponentScreen.
	/// 
	/// This contructor assigns the gamescreen variable to the passed in enum constant. It calls the initialise() function.
	/// @see GameScreen
	/// @param t_gameScreen This is a reference to the enum varaible of current screen. 
	OpponentScreen(GameScreen& t_gameScreen);

	/// @brief Updates the current screen.
	/// 
	/// Changes the alpha value of the background sprite. Changes variable of current screen once alpha hits 0 to DifficultyScreen. 
	/// @param t_dt This is the delta time.
	void update(sf::Time t_dt);

	/// @brief Render Function.
	/// 
	/// Draws the background, buttons and text.
	///@param t_window This is the the render window.
	void render(sf::RenderWindow& t_window);

	/// @brief Proccess Events within the current screen.
	/// 
	/// Checks if the buttons are pressed. If pressed, You choose your opponent.
	/// m_pvcButton -> PlayervsAi, m_cvcButton -> AivsAi, m_pvpButton -> PlayervsPlayer
	/// @param t_event The event that is used in this screen.
	/// @param t_pos The current position of the mouse cursor.
	/// @see s_gameplayState
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);

private:
	// @brief Initialses screen
	/// 
	/// Sets up the m_hud's background texture and resets its alpha value to 0. Calls functions setupButtons() and setupText().
	void initialise();

	/// @brief Sets up Buttons for this current screen.
	/// 
	/// Assigns the three buttons their size, colour, outline, origin and position within the game world.
	void setupButtons();

	/// @brief Sets up the text for this current screen.
	/// 
	/// Assigns the three texts their string, fill colour, font, char size, origin and position.
	void setupText();

	/// <summary>
	/// Button that represents Player vs Ai
	/// </summary>
	sf::RectangleShape m_pvcButton;

	/// <summary>
	/// Button that represents Computer vs Computer
	/// </summary>
	sf::RectangleShape m_cvcButton;

	/// <summary>
	/// Button that represents Player vs Player
	/// </summary>
	sf::RectangleShape m_pvpButton;

	/// <summary>
	/// Text that says "Player vs AI " and appears ontop of m_pvcButton
	/// </summary>
	sf::Text m_pvcText;

	/// <summary>
	/// Text that says "AI vs AI " and appears ontop of m_cvcButton
	/// </summary>
	sf::Text m_cvcText;

	/// <summary>
	///  Text that says "AI vs AI " and appears ontop of m_pvpButton
	/// </summary>
	sf::Text m_pvpText;

};

