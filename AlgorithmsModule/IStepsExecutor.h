#pragma once

#include "Steps/Constants.h"

namespace Algorithms
{

namespace Steps
{
template<class P>
class IStep;
template<class P>
using StepPtr = std::unique_ptr<IStep<P>>;
} // Steps

    using TextsPair = std::pair<const std::string, const std::string>;

    template<class Painter>
    class IStepsExecutor
    {
    public:

        virtual void initialize(const TextsPair&) = 0;
        virtual Steps::EAlgorithmState calculateNextStep() = 0;
        virtual const Steps::StepPtr<Painter>& getCurrentStep() const = 0;
        virtual const Steps::Indices& getFoundPatternIndices() const = 0;
        virtual ~IStepsExecutor() = default;
    };

    template<class P>
    using StepsExecutorPtr = std::unique_ptr<IStepsExecutor<P>>;

} // Algorithms
