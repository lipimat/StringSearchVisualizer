#pragma once

#include <memory>

namespace Algorithms
{
namespace Steps
{

    class IStep
    {
    public:
        virtual ~IStep() = default;
    };

    using StepPtr = std::unique_ptr<IStep>;

} //Steps
} //Algorithms
