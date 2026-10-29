#pragma once

#include <algorithm>
#include <cstddef>

namespace opennow::video
{

constexpr std::size_t MaximumDecodeUnitBytes()
{
    return 2 * 1024 * 1024;
}

constexpr std::size_t MaximumQueuedAccessUnits(int frames_per_second)
{
    const int safe_fps = std::max(1, frames_per_second);
    // A recovered packet gap releases several frames at once. Flushing that
    // burst forces a keyframe resync, which freezes the picture far longer
    // than decoding the backlog (about 8 ms per frame on the Switch).
    return static_cast<std::size_t>(std::clamp((safe_fps + 3) / 4, 2, 16));
}

constexpr int MaximumDecodeQueueDelayMs()
{
    return 150;
}

} // namespace opennow::video
