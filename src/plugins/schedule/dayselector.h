#ifndef DAYSELECTOR_H
#define DAYSELECTOR_H

#include <QWidget>

class QToolButton;
class QLabel;

namespace Schedule
{

class MonthLine;

class DaySelector : public QWidget
{
    Q_OBJECT
public:
    explicit DaySelector(QWidget *parent = 0);

signals:

public slots:
private:
    QToolButton *m_calendarButton;
    QLabel *m_currentLabel;
    MonthLine *m_monthLine;
};

}
#endif // DAYSELECTOR_H
