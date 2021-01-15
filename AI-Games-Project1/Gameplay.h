#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Screen.h"
#include "enum.h"
#include "Algorithm.h"
#include "Board.h"

/// This is the Gameplay Screen class.
/// 
/// Child of Screen class.
class Gameplay : public Screen
{
public:
	/// @brief Constructor of the Gameplay Screen.
	/// 
	/// This contructor assigns the gamescreen variable to the passed in enum constant.
	/// Also sets up the players and the algorithm variables and calls the function addPiecesToPlayers() and initialise().
	/// @see  Player::Player, Algorithm::Algorithm.
	/// @param t_gameScreen This is a reference to the enum varaible of current screen. 
	Gameplay(GameScreen& t_gameScreen);

	/// @brief Updates the current screen.
	/// 
	/// Calls the function backgroundAnimation(), has a gameplay loop which it checks if its not gameover,
	/// changes the turn of the player once they have moved and if its an ai player, Makes the move.
	/// @see Player::getControlledByAI(), Player::getMadeMove(), Player::setMadeMove(bool), Algorithm::makeMove(sf::Time), Board::checkForWin(PieceType).
	/// @param t_dt This is the delta time.
	void update(sf::Time t_dt);

	/// @brief Render Function.
	/// 
	/// Draws the background, table, buttons and text, player pieces and board. Board::render().
	/// @param t_window This is the the render window.
	void render(sf::RenderWindow& t_window);

	/// @brief Proccess Events within the current screen.
	/// 
	/// Moves the players pieces and checks if the buttons are pressed.
	/// @param t_event The event that is used in this screen.
	/// @param t_pos The current position of the mouse cursor.
	/// @see Board::selectTile(sf::Vector2f), Player::processTile(Tile*).
	void processEvents(sf::Event& t_event, sf::Vector2f t_pos);

	/// @brief Sets players if they are controlled by Ai.
	/// Calls the Board::restart() function.
	/// @see Player::setControlledByAI(bool), GameplayStates.
	void start();

private:
	
	/// @brief Animates the background image.
	/// 
	/// changes the alpha value based on AnimationMode , Once alpha reaches 0 it changes screen to MainScreen.
	void backgroundAnimation();

	/// <summary>
	/// Sound effect for selecting the pieces as well as placing.
	/// </summary>
	sf::Sound m_selectSound;

	/// <summary>
	/// Sound buffer for the select sound effect.
	/// </summary>
	sf::SoundBuffer m_soundBuff;

	/// @brief Initialises the gameplay screen.
	/// 
	/// Sets up the m_hud's background texture and resets its alpha value to 0. Sets up board sprite background,
	/// the game over hud, button and text. As well as the current turn text in the gamesceen.
	void initialise();

	/// @brief Adds the pieces to the Players.
	/// 
	/// Adds the coloured pieces to each player based on its PieceType.
	/// @see Board::getPieces(PieceType), Player::AddPiece(*Piece).
	void addPiecesToPlayers();
	
	/// <summary>
	/// 
	/// Bool to say if a player has won the game or not, this stops the gameplay loop.
	/// @see update().
	/// </summary>
	bool m_isGameOver{ false };
	
	/// <summary>
	/// Current turn of the players.
	/// </summary>
	int m_currentTurn{ 0 };
	
	/// <summary>
	/// Instance of Board.
	/// @see Board.
	/// </summary>
	Board m_board;
	
	/// <summary>
	/// Pointer to the Instance of Player.
	/// @see Player.
	/// </summary>
	Player* m_players[2];
	
	/// <summary>
	/// Pointer to the Instance of Algorithm.
	/// @see Algorithm.
	/// </summary>
	Algorithm* m_ai[2];

	/// <summary>
	/// sf::Sprite for representation of the table for which the Board sits on.
	/// </summary>
	sf::Sprite m_boardSprite;
	
	/// <summary>
	/// sf::Texture for the m_boardSprite.
	/// </summary>
	sf::Texture m_boardTexture;

	/// <summary>
	/// Text that shows who won the game once m_isGameover is true.
	/// </summary>
	sf::Text m_gameoverText;

	/// <summary>
	/// The text that displays with the return button that says "Return to Menu".
	/// </summary>
	sf::Text m_returnText;

	/// <summary>
	/// Text that displays the current players turn eg. Red's turn/ Green's Turn.
	/// </summary>
	sf::Text m_currentTurnText;

	/// <summary>
	/// A transparent black overlay that displays over the gamescreen but behind the return button and gameoverText.
	/// </summary>
	sf::RectangleShape m_gameoverHud;

	/// <summary>
	/// The rectangle button that once pressed returns to main menu.
	/// </summary>
	sf::RectangleShape m_returnButton;

};

