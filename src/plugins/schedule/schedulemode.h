#ifndef SCHEDULEMODE_H
#define SCHEDULEMODE_H

#include <QtCore/QObject>

#include <coreplugin/imode.h>
#include <coreplugin/id.h>

class QToolButton;
class QVBoxLayout;

using namespace Core;

namespace Core {
class IWelcomePage;
}

namespace Schedule {

class ScheduleWidget;

namespace Internal {

class ScheduleMode : public Core::IMode
{
    Q_OBJECT
public:
    ScheduleMode();
    ~ScheduleMode();

     void init();

public slots:

signals:

private:


    ScheduleWidget *m_scheduleWidget;
    QWidget *m_modeWidget;

    QToolButton *m_generalButton;
    QToolButton *m_byDayButton;
    QAction *m_generalAction;
    QAction *m_dayAction;

    QVBoxLayout *layout;
};

} // Internal
} // Schedule

#endif // SCHEDULEMODE_H
