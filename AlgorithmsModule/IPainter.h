#pragma once

#include <memory>

namespace Window
{
namespace Visualization
{

    using TextsPair = std::pair<const std::string, const std::string>;

    class IPainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IPainter() = default;
    };

    using PainterPtr = std::shared_ptr<IPainter>;

} // Visualization
} //Window
