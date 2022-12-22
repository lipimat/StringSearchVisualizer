#pragma once

#include "../IStepsExecutor.h"
#include "../Steps/IStep.h"

namespace Algorithms
{
namespace BoyerMoore
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

        void updateMembersForPatternMove(const int /*moveBy*/);
        void fillFoundPatternIndices(const int /*start*/);
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
        std::string m_sourceText;
        std::string m_patternText;
        Steps::Indices m_patternFound;
        std::vector<Steps::StepPtr<Painter>> m_steps;
    };

} // BoyerMoore
} // Algorithms
