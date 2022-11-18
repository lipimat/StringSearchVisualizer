#pragma once

#include "../../AlgorithmsModule/IStepsExecutor.h"

namespace Algorithms
{

    class CStepsExecutorMock final : public IStepsExecutor
    {
    public:
        //stubs
        std::function<void(const TextsPair&)> m_initialize;
        std::function<Steps::EAlgorithmState()> m_calculateNextStep;
        std::function<Steps::StepPtr()> m_getCurrentStep;

        //interface functions
        void initialize(const TextsPair& texts) override { return m_initialize(texts); };
        Steps::EAlgorithmState calculateNextStep() override { return m_calculateNextStep(); };
        const Steps::StepPtr& getCurrentStep() const override { return m_getCurrentStep(); };
    };

} //Algorithms
