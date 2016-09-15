#ifndef ATHLETEMODE_H
#define ATHLETEMODE_H

#include <QtCore/QObject>

#include <coreplugin/imode.h>
#include <coreplugin/id.h>

using namespace Core;

namespace Core {
class IFightBoard;
}

namespace Athlete {

namespace Internal {

class AthleteMode : public Core::IMode
{
    Q_OBJECT
    Q_PROPERTY(int activePlugin READ activePlugin WRITE setActivePlugin NOTIFY activePluginChanged)
public:
    AthleteMode();
    ~AthleteMode();

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
    void addPages(const QList<IFightBoard *> &pages);

    QWidget *m_matchPage;
    QWidget *m_modeWidget;
    QMap<Id, IFightBoard *> m_idPageMap;
    QList<IFightBoard *> m_pluginList;
    int m_activePlugin;
};

} // Internal
} // Athlete

#endif // ATHLETEMODE_H
