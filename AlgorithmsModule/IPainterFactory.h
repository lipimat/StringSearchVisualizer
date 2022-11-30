#pragma once

#include "IPainter.h"

namespace Visualization
{

    struct IPainterFactory
    {
        virtual PainterPtr createBruteForcePainter() const = 0;
        virtual PainterPtr createAutomatonPainter() const = 0;
        virtual ~IPainterFactory() = default;
    };

    using PainterFactoryPtr = std::unique_ptr<IPainterFactory>;

} //Visualization
