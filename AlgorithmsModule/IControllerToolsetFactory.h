#pragma once

namespace Algorithms
{

template<class P>
class IStepsExecutor;
template<class P>
using StepsExecutorPtr = std::unique_ptr<IStepsExecutor<P>>;

    template<class Painter>
    struct IControllerToolsetFactory
    {
        virtual std::string_view createName() const = 0;
        virtual std::string_view createInfo() const = 0;
        virtual StepsExecutorPtr<Painter> createStepsExecutor() const = 0;
        virtual ~IControllerToolsetFactory() = default;
    };

    template<class P>
    using ControllerToolsetFactoryPtr = std::unique_ptr<IControllerToolsetFactory<P>>;

} // Algorithms
