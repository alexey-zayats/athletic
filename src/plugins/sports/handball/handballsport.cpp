#include "handballsport.h"
#include "handballicons.h"

using namespace Handball;
using namespace Handball::Internal;
using namespace Core;

HandballSport::HandballSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(handballLog) << Q_FUNC_INFO;
}

HandballSport::~HandballSport()
{}

QString HandballSport::title() const
{
    return tr("Handball");
}

int HandballSport::priority() const
{
    return 0;
}

Core::Id HandballSport::id() const
{
    return Id("Handball");
}

QIcon HandballSport::icon() const
{
    return Handball::Icons::MODE_HANDBALL.icon ();
}

