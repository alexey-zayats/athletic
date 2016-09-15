#include "tabletennissport.h"
#include "tabletennisicons.h"

using namespace TableTennis;
using namespace TableTennis::Internal;
using namespace Core;

TableTennisSport::TableTennisSport(QObject *parent) :
    ISport(parent)
{
    qCDebug(tabletennisLog) << Q_FUNC_INFO;
}

TableTennisSport::~TableTennisSport()
{}

QString TableTennisSport::title() const
{
    return tr("Table tennis");
}

int TableTennisSport::priority() const
{
    return 0;
}

Core::Id TableTennisSport::id() const
{
    return Id("TableTennis");
}

QIcon TableTennisSport::icon() const
{
    return TableTennis::Icons::MODE_TABLETENNIS.icon ();
}

