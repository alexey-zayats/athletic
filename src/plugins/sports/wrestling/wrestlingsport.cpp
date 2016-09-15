#include "wrestlingsport.h"
#include "wrestlingicons.h"

using namespace Wrestling;
using namespace Wrestling::Internal;
using namespace Core;

WrestlingSport::WrestlingSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(wrestlingLog) << Q_FUNC_INFO;
}

WrestlingSport::~WrestlingSport()
{}

QString WrestlingSport::title() const
{
    return tr("Wrestling");
}

int WrestlingSport::priority() const
{
    return 1;
}

Core::Id WrestlingSport::id() const
{
    return Id("Wrestling");
}

QIcon WrestlingSport::icon() const
{
    return Wrestling::Icons::MODE_WRESTLING.icon ();
}

