#pragma once

#include "../IStepsExecutor.h"
#include "../Steps/IStep.h"

namespace Algorithms
{
namespace BruteForce
{

    template<class Painter>
    class CStepsExecutor final : public IStepsExecutor<Painter>
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;
        const Steps::StepPtr<Painter>& getCurrentStep() const override;
        const Steps::Indices& getFoundPatternIndices() const override;

    private:

        bool patternWontFitToRemainingSource();
        void updateMembersForPatternMove();
        void fillFoundPatternIndices(const int /*start*/);

        std::string m_sourceText;
        std::string m_patternText;
        bool m_shouldMovePattern;
        int m_currentPatternIndex;
        int m_currentSourceIndex;
        Steps::Indices m_patternFound;
        std::vector<Steps::StepPtr<Painter>> m_steps;
    };

} // BruteForce
} // Algorithms
