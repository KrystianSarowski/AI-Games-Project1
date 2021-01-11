#include "PlayerAI.h"

PlayerAI::PlayerAI(Player* t_player):
    m_player(t_player)
{

}

void PlayerAI::makeAMove()
{
    std::vector<std::list<Tile*>> allPossibleMoves = getPossibleMoves();
    std::vector<Piece*> pieces = m_player->getPieces();

    std::pair<Piece*, Tile*> bestMove = std::pair<Piece*, Tile*>(nullptr, nullptr);
    int bestMoveGain = -100;

    m_player->clearSelection();

    for (int i = 0; i < pieces.size(); i++)
    {
        int typeIndex = static_cast<int>(pieces[i]->getType());

        for (auto it = allPossibleMoves[i].begin(); it != allPossibleMoves[i].end(); ++it)
        {
            int moveGain = pieces[i]->getTile()->getGoalCost(typeIndex) - (*it)->getGoalCost(typeIndex);

            if (moveGain > bestMoveGain)
            {
                bestMove.first = pieces[i];
                bestMove.second = (*it);

                bestMoveGain = moveGain;
            }
        }
    }

    m_player->processTile(bestMove.first->getTile());
    m_player->processTile(bestMove.second);
}

std::vector<std::list<Tile*>> PlayerAI::getPossibleMoves()
{
    std::vector<Piece*> pieces = m_player->getPieces();

    std::vector<std::list<Tile*>> allPossibleMoves;

    for (int i = 0; i < pieces.size(); i++)
    {
        m_player->processTile(pieces[i]->getTile());
        allPossibleMoves.push_back(m_player->getMoveList());
    }

    return allPossibleMoves;
}
