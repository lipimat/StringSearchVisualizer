#pragma once

#include "../../AlgorithmsModule/IStepsExecutor.h"
#include "CStepMock.h"

namespace Algorithms
{

    class CStepsExecutorMock final : public IStepsExecutor
    {
    public:
        //stubs
        std::function<void(const TextsPair&)> m_initialize;
        std::function<Steps::EAlgorithmState()> m_calculateNextStep;
        Steps::StepPtr m_getCurrentStep;

        //interface functions
        void initialize(const TextsPair& texts) override { return m_initialize(texts); };
        Steps::EAlgorithmState calculateNextStep() override { return m_calculateNextStep(); };
        const Steps::StepPtr& getCurrentStep() const override { return m_getCurrentStep; };

        // trick so that mock has a copy constructor and we can mock getCurrentStep
        CStepsExecutorMock() : m_getCurrentStep()
        {
        }
        CStepsExecutorMock(const CStepsExecutorMock& rhs) :
            m_initialize(rhs.m_initialize),
            m_calculateNextStep(rhs.m_calculateNextStep)
        {
            if(rhs.m_getCurrentStep != nullptr)
            {
                const auto& stepMockPtr = dynamic_cast<Steps::CStepMock*>(&*rhs.m_getCurrentStep);
                assert(stepMockPtr != nullptr); //only mocks should be put in mock executor
                m_getCurrentStep = std::make_unique<Steps::CStepMock>(*stepMockPtr);
            }
        }
    };

} //Algorithms
