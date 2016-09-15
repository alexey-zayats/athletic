#include "tennissport.h"
#include "tennisicons.h"

using namespace Tennis;
using namespace Tennis::Internal;
using namespace Core;

TennisSport::TennisSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(tennisLog) << Q_FUNC_INFO;
}

TennisSport::~TennisSport()
{}

QString TennisSport::title() const
{
    return tr("Tennis");
}

int TennisSport::priority() const
{
    return 0;
}

Core::Id TennisSport::id() const
{
    return Id("Tennis");
}

QIcon TennisSport::icon() const
{
    return Tennis::Icons::MODE_TENNIS.icon ();
}

