#include "Player.h"

Player::Player(PieceType t_pieceType):
	m_ownedType(t_pieceType),
	m_selectedPiece(nullptr)
{
}

void Player::addPiece(Piece* t_piece)
{
	m_pieces.push_back(t_piece);
}

void Player::setMadeMove(bool t_madeMove)
{

}

void Player::processSelectedTile(Tile* t_selectedTile)
{
	if (m_selectedPiece != nullptr)
	{
		if (t_selectedTile == m_selectedPiece->getTile())
		{
			m_selectedPiece = nullptr;
			m_moveTiles.clear();
			return;
		}

		else
		{
			for (auto it = m_moveTiles.begin(); it != m_moveTiles.end(); ++it)
			{
				if ((*it) == t_selectedTile)
				{
					m_selectedPiece->getTile()->setIsOccupied(false);
					m_selectedPiece->changeTile(t_selectedTile);
					t_selectedTile->setIsOccupied(true);
					m_selectedPiece = nullptr;
					m_moveTiles.clear();
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
		}
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it)
	{
		(*it)->render(t_window);
	}

	sf::CircleShape marker;
	marker.setRadius(8.0f);
	marker.setFillColor(sf::Color::Yellow);
	marker.setOrigin(sf::Vector2f(8.0f, 8.0f));

	for (auto it = m_moveTiles.begin(); it != m_moveTiles.end(); ++it)
	{
		marker.setPosition((*it)->getPosition());

		t_window.draw(marker);
	}
}

bool Player::getMadeMove()
{
	return m_madeMove;
}
