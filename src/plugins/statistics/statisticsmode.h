#ifndef STATISTICSMODE_H
#define STATISTICSMODE_H

#include <QtCore/QObject>

#include <coreplugin/imode.h>
#include <coreplugin/id.h>

using namespace Core;

namespace Core {
class IMatchBoard;
}

namespace Statistics {

namespace Internal {

class StatisticsMode : public Core::IMode
{
    Q_OBJECT
    Q_PROPERTY(int activePlugin READ activePlugin WRITE setActivePlugin NOTIFY activePluginChanged)
public:
    StatisticsMode();
    ~StatisticsMode();

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
    void addPages(const QList<IMatchBoard *> &pages);

    QWidget *m_matchPage;
    QWidget *m_modeWidget;
    QMap<Id, IMatchBoard *> m_idPageMap;
    QList<IMatchBoard *> m_pluginList;
    int m_activePlugin;
};

} // Internal
} // Statistics

#endif // STATISTICSMODE_H
