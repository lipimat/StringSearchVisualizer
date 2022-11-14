#pragma once

#include "qnamespace.h"

namespace Algorithms
{
namespace Steps
{

    enum class EState
    {
        CONTINUE,
        FINISHED
    };

    static constexpr auto TRUE_COMPARISON_COLOR = Qt::green;
    static constexpr auto FALSE_COMPARISON_COLOR = Qt::red;

} //Steps
} //Algorithms
