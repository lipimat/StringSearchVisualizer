#pragma once

namespace Visualization
{
class IPainterFactory;
using PainterFactoryPtr = std::unique_ptr<IPainterFactory>;
}

namespace Algorithms
{

class IController;
using ControllerPtr = std::unique_ptr<IController>;

    struct IControllerCreator
    {
        virtual ControllerPtr createController(const Visualization::PainterFactoryPtr&) const = 0;
        virtual ~IControllerCreator() = default;
    };

    using ControllerCreatorPtr = std::unique_ptr<IControllerCreator>;

} // Algorithms
