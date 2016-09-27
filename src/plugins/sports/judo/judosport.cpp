#include "judosport.h"
#include "judoicons.h"

using namespace Judo;
using namespace Judo::Internal;
using namespace Core;

JudoSport::JudoSport(QObject *parent) :
    ISport(parent)
{
}

JudoSport::~JudoSport()
{}

QString JudoSport::title() const
{
    return tr("Judo");
}

int JudoSport::priority() const
{
    return 0;
}

Core::Id JudoSport::id() const
{
    return Id("Judo");
}

QIcon JudoSport::icon() const
{
    return Judo::Icons::MODE_JUDO.icon ();
}

