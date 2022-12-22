#pragma once

namespace Algorithms
{
namespace Steps
{
    template<class Painter>
    class IStep
    {
    public:
        virtual void accept(const Painter&) const = 0;
        virtual ~IStep() = default;
    };

    template<class P>
    using StepPtr = std::unique_ptr<IStep<P>>;

} // Steps
} // Algorithms
