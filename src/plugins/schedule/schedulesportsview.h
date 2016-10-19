#ifndef SCHEDULESPORTSVIEW_H
#define SCHEDULESPORTSVIEW_H

#include <QTableView>
namespace Schedule
{

class ScheduleSportsView : public QTableView
{
    Q_OBJECT
public:
    ScheduleSportsView(QWidget *parent);
    ~ScheduleSportsView();
};

}
#endif // SCHEDULESPORTSVIEW_H
