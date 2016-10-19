#include "schedulewidget.h"

#include "scheduleicons.h"
#include "generalschedule.h"
#include "bydayschedule.h"

#include <utils/theme/theme.h>

#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QButtonGroup>

using namespace Utils;

namespace Schedule {

ScheduleWidget::ScheduleWidget(QWidget *parent)
    : QWidget(parent),
      m_generalSchedule(0),
      m_byDateSchedule(0),
      m_stack(0)
{
    m_layout = new QVBoxLayout;
    m_layout->setMargin (0);
    m_layout->setSpacing (0);

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_generalSchedule = new QPushButton(this);
    m_generalSchedule->setCheckable (true);
    m_generalSchedule->setIcon (Icons::SCHEDULE_GENERAL.icon ());
    m_generalSchedule->setText ( tr("General") );
    m_generalSchedule->setChecked (true);

    m_byDateSchedule = new QPushButton(this);
    m_byDateSchedule->setCheckable (true);
    m_byDateSchedule->setIcon (Icons::SCHEDULE_BYDAY.icon ());
    m_byDateSchedule->setText ( tr("By day") );
//    m_byDateSchedule->set

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setMargin (0);
    buttonLayout->setSpacing (0);
    buttonLayout->addWidget (m_generalSchedule);
    buttonLayout->addWidget (m_byDateSchedule);
    buttonLayout->addSpacerItem (new QSpacerItem(10, 10, QSizePolicy::Expanding));

    m_stack = new QStackedWidget(this);

    m_general = new GeneralSchedule(this);
    m_byDay = new ByDaySchedule(this);

    m_stack->addWidget (m_general);
    m_stack->addWidget (m_byDay);
    m_stack->setCurrentIndex (0);

    m_layout->addLayout (buttonLayout);
    m_layout->addWidget (m_stack, 1);

    setLayout (m_layout);

    connect(m_generalSchedule, &QPushButton::toggled, this, &ScheduleWidget::scheduleByToggled);
    connect(m_byDateSchedule, &QPushButton::toggled, this, &ScheduleWidget::scheduleByToggled);

//    setStyleSheet ( QLatin1String("border: 0; margin: 0;") );
}

ScheduleWidget::~ScheduleWidget()
{}

void ScheduleWidget::scheduleByToggled(bool on)
{
    if (false == on ) return;
    QPushButton *btn = qobject_cast<QPushButton*> (sender());
    if (btn == m_generalSchedule) {
        m_byDateSchedule->setChecked (false);
        m_stack->setCurrentIndex (0);
        emit generalEnabled();
    }
    if (btn == m_byDateSchedule) {
        m_generalSchedule->setChecked (false);
        m_stack->setCurrentIndex (1);
        emit byDayEnabled();
    }
}

}
