#pragma once

#include "Steps/IStep.h"

namespace Algorithms
{

namespace Steps
{
enum class EAlgorithmState;
} //Steps

    using TextsPair = std::pair<const std::string, const std::string>;

    class IStepsExecutor
    {
    public:

        virtual void initialize(const TextsPair&) = 0;
        virtual Steps::EAlgorithmState calculateNextStep() = 0;
        virtual const Steps::StepPtr& getCurrentStep() const = 0;
        virtual ~IStepsExecutor() = default;
    };

    using StepsExecutorPtr = std::unique_ptr<IStepsExecutor>;

} //Algorithms
