#ifndef MONTHLINE_H
#define MONTHLINE_H

#include <QtWidgets/QWidget>

namespace Schedule
{

class MonthLine : public QWidget
{
    Q_OBJECT
public:
    explicit MonthLine(QWidget *parent = 0);
    ~MonthLine();

signals:

public slots:
};

}

#endif // MONTHLINE_H
