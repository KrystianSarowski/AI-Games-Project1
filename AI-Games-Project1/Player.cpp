#include "Player.h"

Player::Player(PieceType t_pieceType, std::string t_name):
	m_ownedType(t_pieceType),
	m_selectedPiece(nullptr),
	m_name(t_name)
{
}

void Player::addPiece(Piece* t_piece)
{
	m_pieces.push_back(t_piece);
}

void Player::makeAMove(Piece* t_pieceToMove, Tile* t_destTile)
{
	t_pieceToMove->getTile()->setIsOccupied(false);
	t_pieceToMove->setTile(t_destTile);
	t_destTile->setIsOccupied(true);
	setMadeMove(true);
}

void Player::setMadeMove(bool t_madeMove)
{
	m_madeMove = t_madeMove;
}

void Player::setControlledByAI(bool t_isControlledByAI)
{
	m_controlledByAI = t_isControlledByAI;
}

void Player::processTile(Tile* t_selectedTile)
{
	if (m_selectedPiece != nullptr)
	{
		if (t_selectedTile == m_selectedPiece->getTile())
		{
			clearSelection();
			return;
		}

		else
		{
			for (auto it = m_moveTiles.begin(); it != m_moveTiles.end(); ++it)
			{
				if ((*it) == t_selectedTile)
				{
					makeAMove(m_selectedPiece, t_selectedTile);
					clearSelection();
					return;
				}
			}
		}
	}

	for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
	{
		if ((*it)->getTile() == t_selectedTile)
		{
			m_selectedPiece = (*it);
			m_moveTiles = m_selectedPiece->getPossibleMoves();
			return;
		}
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	sf::CircleShape marker;
	marker.setRadius(11.0f);
	marker.setFillColor(sf::Color::Yellow);
	marker.setOrigin(sf::Vector2f(11.0f, 11.0f));

	for (auto it = m_moveTiles.begin(); it != m_moveTiles.end(); ++it)
	{
		marker.setPosition((*it)->getPosition());

		t_window.draw(marker);
	}
}

void Player::clearSelection()
{
	m_selectedPiece = nullptr;
	m_moveTiles.clear();
}

bool Player::getMadeMove()
{
	return m_madeMove;
}

bool Player::getControlledByAI()
{
	return m_controlledByAI;
}

PieceType Player::getOwnedPieceType()
{
	return m_ownedType;
}

std::vector<Piece*> Player::getPieces()
{
	return m_pieces;
}

std::list<Tile*> Player::getMoveList()
{
	return m_moveTiles;
}

std::string Player::getPlayerName()
{
	return m_name;
}