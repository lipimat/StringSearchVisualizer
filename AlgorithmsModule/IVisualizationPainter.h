#pragma once

#include <memory>

namespace Window
{
namespace Visualization
{

    using TextsPair = std::pair<const std::string, const std::string>;

    class IVisualizationPainter
    {
    public:
        virtual void drawBasicScene(const TextsPair&) = 0;
        virtual void cleanWholeScene() = 0;
        virtual ~IVisualizationPainter() = default;
    };

    using VisualizationPainterPtr = std::shared_ptr<IVisualizationPainter>;

} // Visualization
} //Window
