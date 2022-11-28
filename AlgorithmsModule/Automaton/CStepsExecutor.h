#pragma once

#include "IStepsExecutor.h"

namespace Algorithms
{
namespace Automaton
{

    class CStepsExecutor final : public IStepsExecutor
    {
    public:

        void initialize(const TextsPair&) override {};
        Steps::EAlgorithmState calculateNextStep() override {};
        const Steps::StepPtr& getCurrentStep() const override {};
        const Visualization::Indices& getFoundPatternIndices() const override {};
    };

} //BoyerMoore
} //Algorithms
