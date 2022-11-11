#pragma once

#include "qfont.h"
#include "qnamespace.h"

namespace Window
{
namespace Visualization
{
namespace Constants
{

    // rects
    enum class ERectType
    {
        E_SOURCE,
        E_PATTERN
    };

    static constexpr auto RECT_START_X = 0;
    static constexpr auto SOURCE_RECT_Y = 200;
    static constexpr auto PATTERN_RECT_Y = 300;
    static constexpr auto RECT_WIDTH = 80;
    static constexpr auto RECT_HEIGHT = 80;
    static constexpr auto RECT_INITIAL_COLOR = Qt::white;

    // texts
    static const auto TEXT_FONT = QFont("Source Code Pro", 25);

} //Constants
} //Visualization
} //Window
