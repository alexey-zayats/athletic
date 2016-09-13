#include "centralwidget.h"

#include "helpviewer.h"
#include "localhelpmanager.h"

using namespace Help::Internal;

CentralWidget *gStaticCentralWidget = 0;

// -- CentralWidget

CentralWidget::CentralWidget(const Core::Context &context, QWidget *parent)
    : HelpWidget(context, HelpWidget::ModeWidget, parent)
{
    gStaticCentralWidget = this;
}

CentralWidget::~CentralWidget()
{
    // TODO: this shouldn't be done here
    QList<float> zoomFactors;
    QStringList currentPages;
    for (int i = 0; i < viewerCount(); ++i) {
        const HelpViewer * const viewer = viewerAt(i);
        const QUrl &source = viewer->source();
        if (source.isValid()) {
            currentPages.append(source.toString());
            zoomFactors.append(viewer->scale());
        }
    }

    LocalHelpManager::setLastShownPages(currentPages);
    LocalHelpManager::setLastShownPagesZoom(zoomFactors);
    LocalHelpManager::setLastSelectedTab(currentIndex());
}

CentralWidget *CentralWidget::instance()
{
    return gStaticCentralWidget;
}
