#pragma once

#include <memory>

namespace Window
{
namespace Visualization
{

    class IVisualizationPainter
    {
    public:
        virtual void initializeVisualization() = 0;
        virtual ~IVisualizationPainter() = default;
    };

    using VisualizationPainterPtr = std::shared_ptr<IVisualizationPainter>;

} // Visualization
} //Window
