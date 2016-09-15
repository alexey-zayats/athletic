#include "matchicons.h"

namespace Match {
namespace Icons {

const Utils::Icon MODE_MATCH_CLASSIC(
        QLatin1String(":/match/images/mode_match.png"));
const Utils::Icon MODE_MATCH_FLAT({
        {QLatin1String(":/match/images/mode_match_mask.png"), Utils::Theme::IconsBaseColor}});
const Utils::Icon MODE_MATCH_FLAT_ACTIVE({
        {QLatin1String(":/match/images/mode_match_mask.png"), Utils::Theme::IconsModeMatchActiveColor}});

}
}
