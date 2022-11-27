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
        Steps::EAlgorithmState calculateNextStep() override;
        const Steps::StepPtr& getCurrentStep() const override;
        const Visualization::Indices& getFoundPatternIndices() const override;

    private:

        bool patternWontFitToRemainingSource();
        void updateMembersForPatternMove();
        void fillFoundPatternIndices(const int /*start*/);

        std::string m_sourceText;
        std::string m_patternText;
        bool m_shouldMovePattern;
        int m_currentPatternIndex;
        int m_currentSourceIndex;
        Visualization::Indices m_patternFound;
        std::vector<Steps::StepPtr> m_steps;
    };

} //BruteForce
} //Algorithms
