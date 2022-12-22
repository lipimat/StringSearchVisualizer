#pragma once

#include "../ABaseStepsExecutor.h"

namespace Algorithms
{
namespace BruteForce
{

    template<class Painter>
    class CStepsExecutor final : public ABaseStepsExecutor<Painter>
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;

    private:

        bool patternWontFitToRemainingSource();
        void updateMembersForPatternMove();

        bool m_shouldMovePattern;
        int m_currentPatternIndex;
        int m_currentSourceIndex;
    };

} // BruteForce
} // Algorithms
