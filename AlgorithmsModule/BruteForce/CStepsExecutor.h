#pragma once

#include <vector>

#include "../IStepsExecutor.h"
#include "../Steps/Constants.h"

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

        int m_currentPatternIndex;
        int m_currentSourceIndex;
        Steps::StepPtr m_currentStep;
    };

} //BruteForce
} //Algorithms
