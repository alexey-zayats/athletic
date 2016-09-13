
#ifndef HELPINDEXFILTER_H
#define HELPINDEXFILTER_H

#include <coreplugin/locator/ilocatorfilter.h>

#include <QIcon>
#include <QMutex>

namespace Help {
namespace Internal {

class HelpIndexFilter : public Core::ILocatorFilter
{
    Q_OBJECT

public:
    HelpIndexFilter();
    ~HelpIndexFilter();

    // ILocatorFilter
    void prepareSearch(const QString &entry);
    QList<Core::LocatorFilterEntry> matchesFor(QFutureInterface<Core::LocatorFilterEntry> &future,
                                               const QString &entry);
    void accept(Core::LocatorFilterEntry selection) const;
    void refresh(QFutureInterface<void> &future);

    Q_INVOKABLE QSet<QString> searchMatches(const QString &databaseFilePath,
                                          const QString &term, int limit);
signals:
    void linkActivated(const QUrl &link) const;
    void linksActivated(const QMap<QString, QUrl> &links, const QString &key) const;

private:
    void invalidateCache();

    QStringList m_helpDatabases;
    QSet<QString> m_keywordCache;
    QString m_searchTermCache;
    bool m_needsUpdate;
    QMutex m_mutex;
    QIcon m_icon;
};

} // namespace Internal
} // namespace Help

#endif // HELPINDEXFILTER_H
