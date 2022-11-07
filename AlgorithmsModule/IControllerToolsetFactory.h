#pragma once

#include <string_view>

namespace Window
{
class IVisualizationWidget;
}

namespace Algorithms
{

class AVisualizationPainter;

    struct IControllerToolsetFactory
    {
        virtual std::string_view createName() const = 0;
        virtual std::string_view createInfo() const = 0;
        virtual ~IControllerToolsetFactory() = default;
    };

} // Algorithms
