
#ifndef HELP_SEARCHTASKHANDLER_H
#define HELP_SEARCHTASKHANDLER_H

#include <projectexplorer/itaskhandler.h>

QT_FORWARD_DECLARE_CLASS(QUrl)

namespace Help {
namespace Internal {

class SearchTaskHandler : public ProjectExplorer::ITaskHandler
{
    Q_OBJECT

public:
    SearchTaskHandler() {}

    bool canHandle(const ProjectExplorer::Task &task) const;
    void handle(const ProjectExplorer::Task &task);
    QAction *createAction(QObject *parent) const;

signals:
    void search(const QUrl &url);
};

} // namespace Internal
} // namespace Help

#endif // HELP_SEARCHTASKHANDLER_H
