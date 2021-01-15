#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"

/// This is the Difficulty Screen Class.
/// 
/// Child of the Screen class.
class DifficultyScreen : public Screen
{
public:
	/// @brief Constructor of the Difficulty Screen.
	/// 
	/// This contructor assigns the gamescreen variable to the passed in enum constant. It calls the initialise function.
	/// @see initialise().
	/// @param gamescreen This is the enum varaible of current screen. 
	DifficultyScreen(GameScreen& gamescreen);

	/// @brief Updates the current screen.
	/// 
	/// Changes the alpha value of the background sprite. Changes variable of current screen once alpha hits 0. 
	/// @param t_dt This is the delta time.
	void update(sf::Time t_dt);

	/// @brief Render Function.
	/// 
	/// Draws the background, buttons and text.
	///@param t_window This is the the render window.
	void render(sf::RenderWindow& t_window);

	/// @brief Proccess Events within the current screen.
	/// 
	/// Checks if the buttons are pressed.
	/// @param t_event The event that is used in this screen.
	/// @param t_pos The current position of the mouse cursor.
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);

private:
	/// @brief Initialses the background.
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
	/// Button for easy mode against Ai.
	/// </summary>
	sf::RectangleShape m_eButton;

	/// <summary>
	/// Button for normal mode against Ai.
	/// </summary>
	sf::RectangleShape m_mButton;

	/// <summary>
	/// Text to display "easy" in the easy button.
	/// </summary>
	sf::Text m_eText;
	
	/// <summary>
	/// Text that displays "normal" within the normal button.
	/// </summary>
	sf::Text m_mText;

};