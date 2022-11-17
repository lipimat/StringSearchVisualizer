#pragma once

#include "IStepsExecutor.h"
#include "Steps/Constants.h"

namespace Algorithms
{
namespace BruteForce
{

    class CStepsExecutor final : public IStepsExecutor
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EState calculateNextStep() override;
        const Steps::StepPtr& getCurrentStep() const override;

    private:
        std::string m_sourceText;
        std::string m_patternText;

        bool m_shouldMovePattern;
        int m_currentPatternIndex;
        int m_currentSourceIndex;
        std::vector<Steps::StepPtr> m_steps;
    };

} //BruteForce
} //Algorithms
