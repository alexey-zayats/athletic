#include "dayselector.h"
#include "monthline.h"

#include "scheduleicons.h"

#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QDate>

namespace Schedule
{

DaySelector::DaySelector(QWidget *parent)
    : QWidget(parent),
      m_calendarButton(0),
      m_currentLabel(0),
      m_monthLine(0)
{
    /*
      1. Month selector
      2. Current moth, day(?)
      3. Days as a buttons to show by day schedule
    */

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_calendarButton = new QToolButton(this);
    m_calendarButton->setIcon ( Icons::CALENDAR_SELECTOR.icon() );

    m_currentLabel = new QLabel(this);
    m_currentLabel->setText ( QDate::currentDate().toString ( QLatin1String("dd.MM.yyyy") ) );

    m_monthLine = new MonthLine(this);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing (5);
    layout->setMargin (0);

    layout->addWidget (m_calendarButton);
    layout->addWidget (m_currentLabel);
    layout->addWidget (m_monthLine, 1);

    setLayout (layout);
}

}
