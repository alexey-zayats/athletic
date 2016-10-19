#include "bydayschedule.h"

#include <QLabel>

namespace Schedule
{

ByDaySchedule::ByDaySchedule(QWidget *parent) : QMainWindow(parent)
{
    QLabel *l = new QLabel(this);
    l->setText ( tr("By day") );

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

}
