#ifndef GENERALSCHEDULE_H
#define GENERALSCHEDULE_H

#include <QtWidgets/QWidget>

namespace Schedule
{

class DaySelector;
class ScheduleSportsTable;

class GeneralSchedule : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralSchedule(QWidget *parent = 0);

signals:

public slots:
private:
    DaySelector *m_daySelector;
    ScheduleSportsTable *m_table;
};

}

#endif // GENERALSCHEDULE_H
