#pragma once

#include "IStepsExecutor.h"
#include "Steps/Constants.h"

namespace Algorithms
{
namespace BoyerMoore
{

    //this class shall be refactored and merged with brute force executor
    //we should only specialize them at lower level
    class CStepsExecutor final : public IStepsExecutor
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;
        const Steps::StepPtr& getCurrentStep() const override;
        const Visualization::Indices& getFoundPatternIndices() const override;

    private:

        void updateMembersForPatternMove(const int /*moveBy*/);
        void fillFoundPatternIndices(const int /*start*/);
        bool patternWontFitIntoRemainingSource() const;
        std::pair<Visualization::Indices, Visualization::Indices> calculateGoodShiftPreMoveIndices(const int) const;

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
        Visualization::Indices m_patternFound;
        std::vector<Steps::StepPtr> m_steps;
    };

} //BoyerMoore
} //Algorithms
