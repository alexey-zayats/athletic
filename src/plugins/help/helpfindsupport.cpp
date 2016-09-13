
#include "helpfindsupport.h"
#include "helpviewer.h"

using namespace Core;
using namespace Help::Internal;

HelpViewerFindSupport::HelpViewerFindSupport(HelpViewer *viewer)
    : m_viewer(viewer)
{
}

FindFlags HelpViewerFindSupport::supportedFindFlags() const
{
    return FindBackward | FindCaseSensitively;
}

QString HelpViewerFindSupport::currentFindString() const
{
    return m_viewer->selectedText();
}

IFindSupport::Result HelpViewerFindSupport::findIncremental(const QString &txt,
    FindFlags findFlags)
{
    findFlags &= ~FindBackward;
    return find(txt, findFlags, true) ? Found : NotFound;
}

IFindSupport::Result HelpViewerFindSupport::findStep(const QString &txt,
    FindFlags findFlags)
{
    return find(txt, findFlags, false) ? Found : NotFound;
}

bool HelpViewerFindSupport::find(const QString &txt,
    FindFlags findFlags, bool incremental)
{
    bool wrapped = false;
    bool found = m_viewer->findText(txt, findFlags, incremental, false, &wrapped);
    if (wrapped)
        showWrapIndicator(m_viewer);
    return found;
}
