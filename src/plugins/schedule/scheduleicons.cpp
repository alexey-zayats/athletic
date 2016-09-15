#include "scheduleicons.h"

namespace Schedule
{
namespace Icons
{
const Utils::Icon MODE_SCHEDULE_CLASSIC(
        QLatin1String(":/schedule/images/mode_schedule.png"));
const Utils::Icon MODE_SCHEDULE_FLAT({
        {QLatin1String(":/schedule/images/mode_schedule_mask.png"), Utils::Theme::IconsBaseColor}});
const Utils::Icon MODE_SCHEDULE_FLAT_ACTIVE({
        {QLatin1String(":/schedule/images/mode_schedule_mask.png"), Utils::Theme::IconsModeScheduleActiveColor}});
}
}