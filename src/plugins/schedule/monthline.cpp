#include "monthline.h"

namespace Schedule
{

MonthLine::MonthLine(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MonthLine::~MonthLine()
{}

}
