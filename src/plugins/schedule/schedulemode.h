#ifndef SCHEDULEMODE_H
#define SCHEDULEMODE_H

#include <QtCore/QObject>

#include <coreplugin/imode.h>
#include <coreplugin/id.h>

class QToolButton;

using namespace Core;

namespace Core {
class IWelcomePage;
}

namespace Schedule {

namespace Internal {

class ScheduleMode : public Core::IMode
{
    Q_OBJECT
public:
    ScheduleMode();
    ~ScheduleMode();

public slots:

signals:

private:
    QWidget *m_schedulePage;
    QWidget *m_modeWidget;

    QToolButton *m_generalButton;
    QToolButton *m_byDayButton;
    QAction *m_generalAction;
    QAction *m_dayAction;
};

} // Internal
} // Schedule

#endif // SCHEDULEMODE_H
