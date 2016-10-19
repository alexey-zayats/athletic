#ifndef SCHEDULESPORTSTABLE_H
#define SCHEDULESPORTSTABLE_H

#include <QtWidgets/QWidget>

namespace Core{
class ISport;
}

namespace Schedule
{

class ScheduleSportsModel;
class ScheduleSportsView;

class ScheduleSportsTable : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleSportsTable(QWidget *parent = 0);

signals:

public slots:
private:
    ScheduleSportsModel *m_model;
    ScheduleSportsView *m_view;
    QList<Core::ISport*> m_sports;
};
}
#endif // SCHEDULESPORTSTABLE_H
