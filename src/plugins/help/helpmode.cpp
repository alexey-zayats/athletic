
#include "helpmode.h"
#include "helpconstants.h"
#include "helpicons.h"

#include <QCoreApplication>

using namespace Help;
using namespace Help::Internal;

HelpMode::HelpMode(QObject *parent)
  : Core::IMode(parent)
{
    setObjectName(QLatin1String("HelpMode"));
    setContext(Core::Context(Constants::C_MODE_HELP));
    setIcon(Utils::Icon::modeIcon(Icons::MODE_HELP_CLASSIC,
                                  Icons::MODE_HELP_FLAT, Icons::MODE_HELP_FLAT_ACTIVE));
    setDisplayName(QCoreApplication::translate("Help::Internal::HelpMode", "Help"));
    setPriority(Constants::P_MODE_HELP);
    setId(Constants::ID_MODE_HELP);
}
