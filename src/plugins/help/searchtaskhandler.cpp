#include "searchtaskhandler.h"

#include <projectexplorer/task.h>

#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QUrl>

using namespace Help::Internal;

bool SearchTaskHandler::canHandle(const ProjectExplorer::Task &task) const
{
    return !task.description.isEmpty()
            && !task.description.startsWith(QLatin1Char('\n'));
}

void SearchTaskHandler::handle(const ProjectExplorer::Task &task)
{
    const int eol = task.description.indexOf(QLatin1Char('\n'));
    const QUrl url(QLatin1String("https://www.google.com/search?q=") + task.description.left(eol));
    emit search(url);
}

QAction *SearchTaskHandler::createAction(QObject *parent) const
{
    return new QAction(tr("Get Help Online"), parent);
}
