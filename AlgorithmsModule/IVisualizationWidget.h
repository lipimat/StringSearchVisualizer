#pragma once
#include <functional>
#include <QPaintDevice>

namespace Algorithms
{
class AVisualizationPainter;
}
namespace Window
{

    class IVisualizationWidget : public QPaintDevice
    {
    public:
        virtual void updateWithGivenFunction(std::function<void()>) = 0;
        virtual ~IVisualizationWidget() = default;
    };

}
