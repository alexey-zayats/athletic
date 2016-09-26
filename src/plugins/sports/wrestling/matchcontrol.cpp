#include "matchcontrol.h"

namespace Wrestling
{

MatchControl::MatchControl()
{}

MatchControl::~MatchControl()
{}

QString MatchControl::title() const
{
    return tr("Wrestling::MatchControl");
}

int MatchControl::priority() const
{
    return 0;
}

Core::Id MatchControl::id() const
{
    return Id("Wrestling::MatchControl");
}

}
