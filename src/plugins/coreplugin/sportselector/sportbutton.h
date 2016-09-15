#ifndef SPORTBUTTON_H
#define SPORTBUTTON_H

#include <QtCore/QObject>

#include <QIcon>
#include <QWidget>

#include <QTimer>
#include <QPropertyAnimation>

namespace Core {
namespace Internal {

class SportButton : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float fader READ fader WRITE setFader)
public:
    SportButton(QWidget *sporstGrid = 0) :enabled(false), m_sportsGrid(sporstGrid), m_fader(0) {
        animator.setPropertyName("fader");
        animator.setTargetObject(this);
    }
    float fader() { return m_fader; }
    void setFader(float value);

    void fadeIn();
    void fadeOut();

    QIcon icon;
    QString text;
    QString toolTip;
    bool enabled;

private:
    QPropertyAnimation animator;
    QWidget *m_sportsGrid;
    float m_fader;
};

}
}

#endif // SPORTBUTTON_H
