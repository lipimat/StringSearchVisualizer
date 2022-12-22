#pragma once

#include "qfont.h"
#include "qnamespace.h"

namespace Visualization
{
namespace Constants
{

    // rects
    enum class ERectType
    {
        SOURCE,
        PATTERN
    };

    static constexpr auto RECT_START_X = 0;
    static constexpr auto SOURCE_RECT_Y = 200;
    static constexpr auto PATTERN_RECT_Y = 300;
    static constexpr auto RECT_WIDTH = 80;
    static constexpr auto RECT_HEIGHT = 80;
    static constexpr auto RECT_INITIAL_COLOR = Qt::white;

    // texts
    static const auto TEXT_FONT = QFont("Source Code Pro", 25);
    static const auto SMALLER_TEXT_FONT = QFont("Source Code Pro", 15);

    // ellipses
    static constexpr auto ELLIPSE_RADIUS = 60;
    static constexpr auto ELLIPSE_INITIAL_COLOR = Qt::yellow;
    static constexpr auto ELLIPSE_HIGHLIGHT_COLOR = Qt::green;
    static constexpr auto ELLIPSE_START_X = RECT_START_X - ELLIPSE_RADIUS/2;
    static constexpr auto ELLIPSE_Y = PATTERN_RECT_Y;

} // Constants
} // Visualization
