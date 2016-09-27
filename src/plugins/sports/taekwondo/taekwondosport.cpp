#include "taekwondosport.h"
#include "taekwondoicons.h"

using namespace Taekwondo;
using namespace Taekwondo::Internal;
using namespace Core;

TaekwondoSport::TaekwondoSport(QObject *parent) :
    ISport(parent)
{
}

TaekwondoSport::~TaekwondoSport()
{}

QString TaekwondoSport::title() const
{
    return tr("Taekwondo");
}

int TaekwondoSport::priority() const
{
    return 0;
}

Core::Id TaekwondoSport::id() const
{
    return Id("Taekwondo");
}

QIcon TaekwondoSport::icon() const
{
    return Taekwondo::Icons::MODE_TAEKWONDO.icon ();
}

