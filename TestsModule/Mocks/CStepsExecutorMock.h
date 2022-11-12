#pragma once

#include <functional>

#include "../AlgorithmsModule/IStepsExecutor.h"

namespace Algorithms
{

    struct CStepsExecutorMock final : IStepsExecutor
    {
        //stubs
        std::function<void(const TextsPair&)> m_initialize;
        std::function<Steps::EState()> m_calculateNextStep;
        std::function<const Steps::StepPtr()> m_getCurrentStep;

        //interface functions
        void initialize(const TextsPair& texts) override { return m_initialize(texts); };
        Steps::EState calculateNextStep() override { return m_calculateNextStep(); };
        const Steps::StepPtr& getCurrentStep() const override { return m_getCurrentStep(); };
    };

} //Algorithms
