#ifndef SPORTSELECTORWIDGET_H
#define SPORTSELECTORWIDGET_H

#include <QIcon>
#include <QWidget>

#include <QTimer>
#include <QPropertyAnimation>

QT_BEGIN_NAMESPACE
class QAction;
QT_END_NAMESPACE

namespace Core {

class OlympicSport;

namespace Internal {

class SportsGrid;
class SportsButton;

class SportSelectorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SportSelectorWidget(QAction *sportSelectorAction, QWidget *parent = 0);
    ~SportSelectorWidget();

    void setVisible(bool visible);
    void toggleVisible();

    void sportsChanged(int);

protected:
    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);

signals:

public slots:
private:
    void doLayout(bool keepSize);

    QAction *m_sportsAction;
    SportsGrid *m_sportsGrid;
    OlympicSport *m_olympicSport;
};

}
}

#endif // SPORTSELECTORWIDGET_H

