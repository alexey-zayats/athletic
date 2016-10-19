#include "schedulesportsview.h"

#include <QHeaderView>

namespace Schedule
{

ScheduleSportsView::ScheduleSportsView(QWidget *parent) :
    QTableView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectItems);
    horizontalHeader ()->hide();
    verticalHeader ()->hide();
    setShowGrid(false);
}

ScheduleSportsView::~ScheduleSportsView()
{}

}
