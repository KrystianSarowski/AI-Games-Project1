#include "Algorithm.h"

Algorithm::Algorithm(Player* t_player, Board* t_board) :
    m_player(t_player),
    m_board(t_board)
{

}

int Algorithm::miniMax(Evaluation& t_evaluation, PieceType t_type, int t_depth, bool t_maximizing)
{
    if (t_depth == 0)
    {
        return m_board->calculateValue(static_cast<PieceType>((static_cast<int>(t_type) + 1) % 2));
    }

    std::vector<std::list<Tile*>> allPossibleMoves = getPossibleMoves(t_type);
    std::vector<Piece*> pieces = m_board->getPieces(t_type);

    if (t_maximizing)
    {
        for (int i = 0; i < pieces.size(); i++)
        {
            int typeIndex = static_cast<int>(pieces[i]->getType());

            for (auto it = allPossibleMoves[i].begin(); it != allPossibleMoves[i].end(); ++it)
            {
                Evaluation tempEval;

                tempEval.m_piece = pieces[i];
                tempEval.m_targetTile = (*it);
                tempEval.m_alphaPruning = t_evaluation.m_alphaPruning;
                tempEval.m_betaPruning = t_evaluation.m_betaPruning;

                Tile* prevTile = pieces[i]->getTile();
                Piece* piece = pieces[i];

                simulateMove(tempEval.m_piece, tempEval.m_targetTile);

                int cost = miniMax(tempEval, static_cast<PieceType>((static_cast<int>(t_type) + 1) % 2), t_depth - 1, false);

                simulateMove(piece, prevTile);

                

                if(t_evaluation.m_alphaPruning < cost)
                {
                    t_evaluation.m_piece = pieces[i];
                    t_evaluation.m_targetTile = (*it);
                    t_evaluation.m_alphaPruning = cost;

                    if (t_evaluation.m_alphaPruning >= t_evaluation.m_betaPruning)
                    {
                        return t_evaluation.m_alphaPruning;
                    }
                }
            }
        }

        return t_evaluation.m_alphaPruning;
    }

    else
    {
        for (int i = 0; i < pieces.size(); i++)
        {
            int typeIndex = static_cast<int>(pieces[i]->getType());

            for (auto it = allPossibleMoves[i].begin(); it != allPossibleMoves[i].end(); ++it)
            {
                Evaluation tempEval;

                tempEval.m_piece = pieces[i];
                tempEval.m_targetTile = (*it);
                tempEval.m_alphaPruning = t_evaluation.m_alphaPruning;
                tempEval.m_betaPruning = t_evaluation.m_betaPruning;

                Tile* prevTile = pieces[i]->getTile();
                Piece* piece = pieces[i];

                simulateMove(tempEval.m_piece, tempEval.m_targetTile);

                int cost = miniMax(tempEval, static_cast<PieceType>(static_cast<int>(t_type) + 1 % 2), t_depth - 1, true);

                simulateMove(piece, prevTile);

                if (t_evaluation.m_betaPruning > cost)
                {
                    t_evaluation.m_piece = pieces[i];
                    t_evaluation.m_targetTile = (*it);
                    t_evaluation.m_betaPruning = cost;

                    if (t_evaluation.m_betaPruning <= t_evaluation.m_alphaPruning)
                    {
                        return t_evaluation.m_betaPruning;
                    }
                }
            }
        }

        return t_evaluation.m_betaPruning;
    }
}

void Algorithm::calculateMove()
{     
    m_moveEvaluation.m_alphaPruning = INT_MIN;
    m_moveEvaluation.m_betaPruning = INT_MAX;

    miniMax(m_moveEvaluation, m_player->m_ownedType, 3, true);

    m_player->processTile(m_moveEvaluation.m_piece->getTile());
}

void Algorithm::makeMove(sf::Time t_dt)
{
    if (!m_moveCalculated)
    {
        calculateMove();
        m_moveCalculated = true;
        m_moveDelay = sf::seconds(m_delayTime);
    }
    else
    {
        m_moveDelay -= t_dt;

        if (m_moveDelay <= sf::seconds(0.0f))
        {
            m_player->processTile(m_moveEvaluation.m_targetTile);
            m_moveCalculated = false;
        }
    }
}

void Algorithm::simulateMove(Piece* t_piece, Tile* t_tile)
{
    t_piece->getTile()->setIsOccupied(false);
    t_piece->setTile(t_tile);
    t_tile->setIsOccupied(true);
}

std::vector<std::list<Tile*>> Algorithm::getPossibleMoves(PieceType t_type)
{
    std::vector<Piece*> pieces = m_board->getPieces(t_type);

    std::vector<std::list<Tile*>> allPossibleMoves;

    for (int i = 0; i < pieces.size(); i++)
    {
        allPossibleMoves.push_back(pieces[i]->getPossibleMoves());
    }

    return allPossibleMoves;
}
