#include "schedulesportstable.h"
#include "schedulesportsmodel.h"
#include "schedulesportsview.h"

#include <QVBoxLayout>

namespace Schedule {


ScheduleSportsTable::ScheduleSportsTable(QWidget *parent)
    : QWidget(parent),
      m_model(0),
      m_view(0)
{
    m_model = new ScheduleSportsModel();

    m_view = new ScheduleSportsView(this);
    m_view->setModel (m_model);

    m_view->setColumnWidth(0,100);
    for (int col = 1; col < m_model->columnCount (); col++)
    {
       m_view->setColumnWidth(col,32);
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin (0);
    layout->setSpacing (0);

    layout->addWidget (m_view, 1);

    setLayout (layout);
}

}
