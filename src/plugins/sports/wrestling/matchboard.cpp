#include "matchboard.h"

namespace Wrestling
{

MatchBoard::MatchBoard()
{
}

MatchBoard::~MatchBoard()
{
}

QString MatchBoard::title() const
{
    return tr("Scoreboard");
}

int MatchBoard::priority() const
{
    return 0;
}

Core::Id MatchBoard::id() const
{
    return Core::Id("Wrestling::MatchBoard");
}

}
