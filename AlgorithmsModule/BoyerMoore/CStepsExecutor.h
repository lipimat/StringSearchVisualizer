#pragma once

#include "../ABaseStepsExecutor.h"

namespace Algorithms
{
namespace BoyerMoore
{

    template<class Painter>
    class CStepsExecutor final : public ABaseStepsExecutor<Painter>
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;

    private:

        void updateMembersForPatternMove(const int /*moveBy*/);
        bool patternWontFitIntoRemainingSource() const;
        std::pair<Steps::Indices, Steps::Indices> calculateGoodShiftPreMoveIndices(const int) const;

        void initializeBadShiftTable();
        std::unordered_map<char, int> m_badShiftTable;

        void initializeGoodShiftTable();
        std::vector<int> calculateSuffixesForGoodShiftTable() const;
        std::vector<int> m_goodShiftTable;

        int m_currentPatternIndex;
        int m_currentSourceIndex;
        int m_patternLastMovedBy;
        bool m_shouldMovePattern;
        bool m_analyzeNextShift;
    };

} // BoyerMoore
} // Algorithms
