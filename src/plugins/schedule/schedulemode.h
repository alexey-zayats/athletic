#ifndef SCHEDULEMODE_H
#define SCHEDULEMODE_H

#include <QtCore/QObject>

#include <coreplugin/imode.h>
#include <coreplugin/id.h>

using namespace Core;

namespace Core {
class IWelcomePage;
}

namespace Schedule {

namespace Internal {

class ScheduleMode : public Core::IMode
{
    Q_OBJECT
    Q_PROPERTY(int activePlugin READ activePlugin WRITE setActivePlugin NOTIFY activePluginChanged)
public:
    ScheduleMode();
    ~ScheduleMode();

    void activated();
    void initPlugins();
    int activePlugin() const { return m_activePlugin; }

public slots:
    void setActivePlugin(int pos)
    {
        if (m_activePlugin != pos) {
            m_activePlugin = pos;
            emit activePluginChanged(pos);
        }
    }
    void pluginAdded(QObject *obj);

signals:
    void activePluginChanged(int pos);

private:
    void schedulePluginAdded(QObject*);
    void addPages(const QList<IWelcomePage *> &pages);

    QWidget *m_schedulePage;
    QWidget *m_modeWidget;
    QMap<Id, IWelcomePage *> m_idPageMap;
    QList<IWelcomePage *> m_pluginList;
    int m_activePlugin;
};

} // Internal
} // Schedule

#endif // SCHEDULEMODE_H
