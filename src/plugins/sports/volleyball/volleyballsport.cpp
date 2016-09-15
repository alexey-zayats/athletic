#include "volleyballsport.h"
#include "volleyballicons.h"

using namespace Volleyball;
using namespace Volleyball::Internal;
using namespace Core;

VolleyballSport::VolleyballSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(volleyballLog) << Q_FUNC_INFO;
}

VolleyballSport::~VolleyballSport()
{}

QString VolleyballSport::title() const
{
    return tr("Volleyball");
}

int VolleyballSport::priority() const
{
    return 1;
}

Core::Id VolleyballSport::id() const
{
    return Id("Volleyball");
}

QIcon VolleyballSport::icon() const
{
    return Volleyball::Icons::MODE_VOLLEYBALL.icon ();
}

