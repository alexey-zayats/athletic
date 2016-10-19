#ifndef SCHEDULESPORTSMODEL_H
#define SCHEDULESPORTSMODEL_H

#include <QAbstractTableModel>

class QItemDelegate;

namespace Core {
class ISport;
}

namespace Schedule
{

class ScheduleSportsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ScheduleSportsModel();
    ~ScheduleSportsModel();

    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
private:
    QList<Core::ISport*> m_sports;
    int rows;
    int cols;
};

}
#endif // SCHEDULESPORTSMODEL_H
