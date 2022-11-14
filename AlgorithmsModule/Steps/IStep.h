#pragma once

#include <memory>
#include <vector>

#include "../IPainter.h"

namespace Algorithms
{
namespace Steps
{

    class IStep
    {
    public:
        virtual void accept(const Window::Visualization::PainterPtr&) const = 0;
        virtual ~IStep() = default;
    };

    using StepPtr = std::unique_ptr<IStep>;

} //Steps
} //Algorithms
