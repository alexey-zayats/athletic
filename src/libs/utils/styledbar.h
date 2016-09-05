
#ifndef STYLEDBAR_H
#define STYLEDBAR_H

#include "utils_global.h"

#include <QWidget>

namespace Utils {

class ATHLETIC_UTILS_EXPORT StyledBar : public QWidget
{
    Q_OBJECT
public:
    StyledBar(QWidget *parent = 0);
    void setSingleRow(bool singleRow);
    bool isSingleRow() const;

    void setLightColored(bool lightColored);
    bool isLightColored() const;

protected:
    void paintEvent(QPaintEvent *event);
};

class ATHLETIC_UTILS_EXPORT StyledSeparator : public QWidget
{
    Q_OBJECT
public:
    StyledSeparator(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *event);
};

} // Utils

#endif // STYLEDBAR_H
