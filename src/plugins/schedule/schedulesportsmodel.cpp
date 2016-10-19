#include "schedulesportsmodel.h"

#include <utils/theme/theme.h>
#include <extensionsystem/pluginmanager.h>
#include <coreplugin/isport.h>

#include <QItemDelegate>
#include <QDate>

using namespace ExtensionSystem;
using namespace Core;
using namespace Utils;


namespace Schedule
{

static bool lessThanBySportTitle(const ISport *a, const ISport *b)
{
    return a->title() < b->title();
}


ScheduleSportsModel::ScheduleSportsModel()
{
    m_sports = PluginManager::getObjects<Core::ISport>();
    qSort(m_sports.begin(), m_sports.end(), lessThanBySportTitle);
    rows = m_sports.size ();
    cols = QDate::currentDate ().daysInMonth () + 1;
}

ScheduleSportsModel::~ScheduleSportsModel()
{
}

QVariant ScheduleSportsModel::data(const QModelIndex &index, int role) const
{
    int col = index.column();
    int row = index.row ();

    if ( 0 == col) {
        switch (role) {
        case Qt::DisplayRole:
            return m_sports.at(row)->title ();
        case Qt::DecorationRole:
            return m_sports.at(row)->icon ();
        case Qt::SizeHintRole:
            return QSize(48, 48);
        case Qt::BackgroundRole:
            return QBrush( athleticTheme ()->color (Theme::BackgroundColorDark));
        }
    } else {
        switch (role) {
        case Qt::DisplayRole:
            return  QString( QLatin1String("%1x%2") ).arg(index.column ()).arg(index.row ());
//        case Qt::DecorationRole:
//            return m_sports.at(row)->icon ();
        case Qt::SizeHintRole:
            return QSize(48, 48);
        case Qt::BackgroundRole:
            return QBrush( athleticTheme ()->color (Theme::BackgroundColorDark));
        }
    }
    return QVariant();
}

int ScheduleSportsModel::rowCount(const QModelIndex &/*parent*/) const
{
    return rows;
}

int ScheduleSportsModel::columnCount(const QModelIndex &/*parent*/) const
{
    return cols;
}

Qt::ItemFlags ScheduleSportsModel::flags(const QModelIndex &/*index*/) const
{
    return Qt::ItemIsSelectable;
}

}
