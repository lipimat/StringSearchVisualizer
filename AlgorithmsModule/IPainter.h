#pragma once

#include "qnamespace.h"

namespace Visualization
{

    using TextsPair = std::pair<const std::string, const std::string>;
    using Indices = std::vector<int>;

    class IPainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void highlightRects(const Indices&, const Indices&, const Qt::GlobalColor) = 0;
        virtual void movePattern() = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IPainter() = default;
    };

    using PainterPtr = std::unique_ptr<IPainter>;

} // Visualization
