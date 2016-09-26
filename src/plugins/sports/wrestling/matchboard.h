#ifndef MATCHBOARD_H
#define MATCHBOARD_H

#include "coreplugin/imatchboard.h"

namespace Wrestling
{

class MatchBoard : public Core::IMatchBoard
{
public:
    MatchBoard();
    ~MatchBoard();

    QString title() const;
    int priority() const;
    Core::Id id() const;
};

}

#endif // FIGHTBOARD_H
