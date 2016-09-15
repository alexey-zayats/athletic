#include "statisticsicons.h"

using namespace Utils;

namespace Statistics {
namespace Icons {

const Utils::Icon MODE_STATISTICS_CLASSIC(
        QLatin1String(":/statistics/images/mode_statistics.png"));
const Utils::Icon MODE_STATISTICS_FLAT({
        {QLatin1String(":/statistics/images/mode_statistics_mask.png"), Utils::Theme::IconsBaseColor}});
const Utils::Icon MODE_STATISTICS_FLAT_ACTIVE({
        {QLatin1String(":/statistics/images/mode_statistics_mask.png"), Utils::Theme::IconsModeAthleteActiveColor}});
}
}
