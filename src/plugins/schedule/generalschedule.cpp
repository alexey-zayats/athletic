#include "generalschedule.h"
#include "dayselector.h"
#include "schedulesportstable.h"

#include <QVBoxLayout>

namespace Schedule
{

GeneralSchedule::GeneralSchedule(QWidget *parent)
    : QWidget(parent),
      m_daySelector(0),
      m_table(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_daySelector = new DaySelector(this);
    m_table = new ScheduleSportsTable(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing (0);
    layout->setMargin (0);

    layout->addWidget (m_daySelector);
    layout->addWidget (m_table, 1);

    setLayout (layout);
}

}
