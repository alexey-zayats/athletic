#include "olympicsport.h"

#include "utils/theme/theme.h"
#include "utils/icon.h"

#include "../coreicons.h"

using namespace Utils;

namespace Core
{
OlympicSport::OlympicSport(QObject *parent) :
    ISport(parent)
{}

OlympicSport::~OlympicSport()
{}

QString OlympicSport::title() const
{
    return tr("Olympic");
}

int OlympicSport::priority() const
{
    return 0;
}

Core::Id OlympicSport::id() const
{
    return Id("Olympic");
}

QIcon OlympicSport::icon() const
{
    return athleticTheme()->flag(Theme::FlatSideBarIcons)
            ? Icons::SELECT_SPORTS_FLAT.icon()
            : Icons::SELECT_SPORTS_CLASSIC.icon();
}

}
