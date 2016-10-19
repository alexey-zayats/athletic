#ifndef SCHEDULEWIDGET_H
#define SCHEDULEWIDGET_H

#include <QtWidgets/QWidget>

class QPushButton;
class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;

namespace Schedule
{

class GeneralSchedule;
class ByDaySchedule;

class ScheduleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScheduleWidget(QWidget *parent = 0);
    ~ScheduleWidget();

signals:
    void generalEnabled();
    void byDayEnabled();

public slots:
    void scheduleByToggled(bool on);

private:
    QPushButton *m_generalSchedule;
    QPushButton *m_byDateSchedule;
    QStackedWidget *m_stack;

    QVBoxLayout *m_layout;

    GeneralSchedule *m_general;
    ByDaySchedule *m_byDay;
};
}
#endif // SCHEDULEWIDGET_H
