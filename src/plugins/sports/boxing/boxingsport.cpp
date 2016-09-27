#include "boxingsport.h"
#include "boxingicons.h"

using namespace Boxing;
using namespace Boxing::Internal;
using namespace Core;

BoxingSport::BoxingSport(QObject *parent) :
    ISport(parent)
{
}

BoxingSport::~BoxingSport()
{}

QString BoxingSport::title() const
{
    return tr("Boxing");
}

int BoxingSport::priority() const
{
    return 0;
}

Core::Id BoxingSport::id() const
{
    return Id("Boxing");
}

QIcon BoxingSport::icon() const
{
    return Boxing::Icons::MODE_BOXING.icon ();
}

