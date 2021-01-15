#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "enum.h"
/// This is MainScreen class
/// 
/// Child of Screen
class MainScreen : public Screen
{
public:
	/// @brief Constructor of the MainScreen.
	/// 
	/// This contructor assigns the gamescreen variable to the passed in enum constant. It calls the initialise() function.
	/// @see GameScreen
	/// @param t_gameScreen This is a reference to the enum varaible of current screen. 
	MainScreen(GameScreen& t_gameScreen);

	/// @brief Updates the current screen.
	/// 
	/// Changes the alpha value of the background sprite. Changes variable of current screen once alpha hits 0 to OpponentScreen. 
	/// @param t_dt This is the delta time.
	void update(sf::Time t_dt);

	/// @brief Render Function.
	/// 
	/// Draws the background, buttons and text.
	///@param t_window This is the the render window.
	void render(sf::RenderWindow& t_window);

	/// @brief Proccess Events within the current screen.
	/// 
	/// Checks if the buttons are pressed. If pressed, You either go to OpponentScreen or quit the game
	/// @param t_event The event that is used in this screen.
	/// @param t_pos The current position of the mouse cursor.
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);
	
private:
	/// @brief Initialses screen
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
	/// Button that is used to go to OpponentScreen
	/// </summary>
	sf::RectangleShape m_playButton;

	/// <summary>
	/// Button that is used to quit the game
	/// </summary>
	sf::RectangleShape m_quitButton;

	/// <summary>
	/// Text that says "Play" and appears ontop of m_playButton
	/// </summary>
	sf::Text m_playText;

	/// <summary>
	/// Text that says "Quit" and appears ontop of m_quitButton
	/// </summary>
	sf::Text m_quitText;

};

