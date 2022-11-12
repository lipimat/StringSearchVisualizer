#pragma once

#include <string_view>
#include <memory>

#include "IStepsExecutor.h"

namespace Algorithms
{

    struct IControllerToolsetFactory
    {
        virtual std::string_view createName() const = 0;
        virtual std::string_view createInfo() const = 0;
        virtual StepsExecutorPtr createStepsExecutor() const = 0;
        virtual ~IControllerToolsetFactory() = default;
    };

    using ControllerToolsetFactoryPtr = std::unique_ptr<IControllerToolsetFactory>;

} // Algorithms
