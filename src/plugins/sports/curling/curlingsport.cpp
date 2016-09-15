#include "curlingsport.h"
#include "curlingicons.h"

using namespace Curling;
using namespace Curling::Internal;
using namespace Core;

CurlingSport::CurlingSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(curlingLog) << Q_FUNC_INFO;
}

CurlingSport::~CurlingSport()
{}

QString CurlingSport::title() const
{
    return tr("Curling");
}

int CurlingSport::priority() const
{
    return 0;
}

Core::Id CurlingSport::id() const
{
    return Id("Curling");
}

QIcon CurlingSport::icon() const
{
    return Curling::Icons::MODE_CURLING.icon ();
}

