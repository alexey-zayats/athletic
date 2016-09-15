#include "canoeingsport.h"
#include "canoeingicons.h"

using namespace Canoeing;
using namespace Canoeing::Internal;
using namespace Core;

CanoeingSport::CanoeingSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(canoeingLog) << Q_FUNC_INFO;
}

CanoeingSport::~CanoeingSport()
{}

QString CanoeingSport::title() const
{
    return tr("Canoeing");
}

int CanoeingSport::priority() const
{
    return 0;
}

Core::Id CanoeingSport::id() const
{
    return Id("Canoeing");
}

QIcon CanoeingSport::icon() const
{
    return Canoeing::Icons::MODE_CANOEING.icon ();
}

