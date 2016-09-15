#include "rowingsport.h"
#include "rowingicons.h"

using namespace Rowing;
using namespace Rowing::Internal;
using namespace Core;

RowingSport::RowingSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(rowingLog) << Q_FUNC_INFO;
}

RowingSport::~RowingSport()
{}

QString RowingSport::title() const
{
    return tr("Rowing");
}

int RowingSport::priority() const
{
    return 0;
}

Core::Id RowingSport::id() const
{
    return Id("Rowing");
}

QIcon RowingSport::icon() const
{
    return Rowing::Icons::MODE_ROWING.icon ();
}

