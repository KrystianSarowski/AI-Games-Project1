#pragma once
#include "Player.h"
class PlayerAI 
{
public:

	PlayerAI(Player* t_player);

	void makeAMove();

private:

	Player* m_player;

	std::vector<std::list<Tile*>> getPossibleMoves();
};

