#pragma once

#include "../../AlgorithmsModule/IStepsExecutor.h"
#include "CStepMock.h"

namespace Algorithms
{

    template<class Painter>
    class CStepsExecutorMock final : public IStepsExecutor<Painter>
    {
    public:
        //stubs
        std::function<void(const TextsPair&)> m_initialize;
        std::function<Steps::EAlgorithmState()> m_calculateNextStep;
        Steps::StepPtr<Painter> m_getCurrentStep;
        Steps::Indices m_foundPatternIndices;


        //interface functions
        void initialize(const TextsPair& texts) override { return m_initialize(texts); };
        Steps::EAlgorithmState calculateNextStep() override { return m_calculateNextStep(); };
        const Steps::StepPtr<Painter>& getCurrentStep() const override { return m_getCurrentStep; };
        const Steps::Indices& getFoundPatternIndices() const override { return m_foundPatternIndices; };

        // trick so that mock has a copy constructor and we can mock getCurrentStep
        CStepsExecutorMock() : m_getCurrentStep()
        {
        }
        CStepsExecutorMock(const CStepsExecutorMock& rhs) :
            m_initialize(rhs.m_initialize),
            m_calculateNextStep(rhs.m_calculateNextStep),
            m_foundPatternIndices(rhs.m_foundPatternIndices)
        {
            if(rhs.m_getCurrentStep != nullptr)
            {
                const auto& stepMockPtr = dynamic_cast<Steps::CStepMock<Painter>*>(&*rhs.m_getCurrentStep);
                assert(stepMockPtr != nullptr); //only mocks should be put in mock executor
                m_getCurrentStep = std::make_unique<Steps::CStepMock<Painter>>(*stepMockPtr);
            }
        }
    };

} //Algorithms
