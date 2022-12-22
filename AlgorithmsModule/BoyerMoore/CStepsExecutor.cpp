#include "CStepsExecutor.h"
#include "IPainterFactory.h"
#include "../SupportedAlgorithmsAlphabet.h"
#include "../Steps/CComparison.h"
#include "../Steps/CMovePattern.h"

namespace Algorithms
{
namespace BoyerMoore
{

    template<class Painter>
    void CStepsExecutor<Painter>::initialize(const TextsPair& texts)
    {
        ABaseStepsExecutor<Painter>::initialize(texts);
        m_currentPatternIndex = this->m_patternText.size() - 1; // we start from end of pattern
        m_currentSourceIndex = 0;
        m_patternLastMovedBy = 0;
        m_shouldMovePattern = false;
        m_analyzeNextShift = false;
        m_badShiftTable.clear();
        m_goodShiftTable.clear();

        initializeBadShiftTable();
        initializeGoodShiftTable();
    }

    template<class Painter>
    Steps::EAlgorithmState CStepsExecutor<Painter>::calculateNextStep()
    {
        auto returnState = Steps::EAlgorithmState::CONTINUE;

        if(patternWontFitIntoRemainingSource())
            returnState = Steps::EAlgorithmState::FINISHED;
        else if(m_shouldMovePattern)
        {
            m_shouldMovePattern = false;
            this->m_steps.push_back(std::make_unique<Steps::CMovePattern<Painter>>(m_patternLastMovedBy));
            m_patternLastMovedBy = 0;
        }
        else if(m_analyzeNextShift)
        {
            m_analyzeNextShift = false;
            const int goodShiftMove = m_goodShiftTable[m_currentPatternIndex];
            const int badShiftMove = m_badShiftTable[this->m_sourceText[m_currentPatternIndex + m_currentSourceIndex]] -
                    this->m_patternText.size() + 1 + m_currentPatternIndex;
            int shouldMoveBy = 0;
            std::pair<Steps::Indices, Steps::Indices> indices;
            if(goodShiftMove >= badShiftMove)
            {
                shouldMoveBy = goodShiftMove;
                indices = calculateGoodShiftPreMoveIndices(shouldMoveBy);
            }
            else
            {
                shouldMoveBy = badShiftMove;
                if(shouldMoveBy != this->m_patternText.size()) // allign to specific character
                {
                    indices.first.push_back(m_currentSourceIndex + m_currentPatternIndex);
                    indices.second.push_back(this->m_patternText.size() - shouldMoveBy - 1);
                }
            }
            if(indices.first.empty() && indices.second.empty()) //couldnt resolve anything, will move by whole pattern
            {
                indices.first.clear();
                for(int i = 0; i < this->m_patternText.size(); ++i)
                    indices.second.push_back(i);
            }
            this->m_steps.push_back(std::make_unique<Steps::CComparison<Painter>>
                              (indices.first, indices.second, Steps::EComparisonType::IDLE));
            updateMembersForPatternMove(shouldMoveBy);
        }
        else
        {
            const auto comparisonSourceIndex = m_currentSourceIndex + m_currentPatternIndex;
            const auto comparisonPatternIndex = m_currentPatternIndex;

            const auto isCurrentSourceIndexInBound = comparisonSourceIndex <= (this->m_sourceText.size() - 1);
            const auto isCurrentPatternIndexInBound = comparisonPatternIndex >= 0;
            assert(isCurrentSourceIndexInBound);
            assert(isCurrentPatternIndexInBound);

            Steps::EComparisonType comparisonType;
            if(this->m_patternText[comparisonPatternIndex] == this->m_sourceText[comparisonSourceIndex])
            {
                comparisonType = Steps::EComparisonType::MATCH;
                m_currentPatternIndex--;
                if(m_currentPatternIndex < 0) //out of bounds, we loop
                {
                    this->fillFoundPatternIndices(m_currentSourceIndex);
                    updateMembersForPatternMove(this->m_patternText.size());
                }
            }
            else
            {
                m_analyzeNextShift = true;
                comparisonType = Steps::EComparisonType::MISMATCH;
            }
            this->m_steps.push_back(std::make_unique<Steps::CComparison<Painter>>
                              (Steps::Indices{comparisonSourceIndex}, Steps::Indices{comparisonPatternIndex}, comparisonType));
        }

        return returnState;
    }

    template<class Painter>
    void CStepsExecutor<Painter>::updateMembersForPatternMove(const int moveBy)
    {
        m_currentPatternIndex = this->m_patternText.size() - 1;
        m_currentSourceIndex += moveBy;
        m_patternLastMovedBy = moveBy;
        m_shouldMovePattern = true;
    }

    template<class Painter>
    bool CStepsExecutor<Painter>::patternWontFitIntoRemainingSource() const
    {
        const int spaceLeft = this->m_sourceText.size() - this->m_patternText.size(); //to avoid overflow and cast to ull
        return m_currentSourceIndex > spaceLeft;
    }

    template<class Painter>
    std::pair<Steps::Indices, Steps::Indices> CStepsExecutor<Painter>::calculateGoodShiftPreMoveIndices
        (const int moveBy) const
    {
        Steps::Indices sourceIndices, patternIndices;
        const int comparedBeforeMiss = this->m_patternText.size() - m_currentPatternIndex - 1;
        int sourceIdx = m_currentSourceIndex + this->m_patternText.size() - 1;
        int patternIdx = this->m_patternText.size() - moveBy - 1;
        if(comparedBeforeMiss == 0) //special case, we failed comparison immediatly
        {
            if(patternIdx >= 0) // in case we have 1 letter pattern, we won't highlight anything
            {
                sourceIndices.push_back(sourceIdx);
                patternIndices.push_back(patternIdx);
            }
        }
        else
        {
            for(int i = 0; i < comparedBeforeMiss; ++i)
            {
                if(patternIdx < 0) // we are before start of pattern
                    break;
                sourceIndices.push_back(sourceIdx);
                patternIndices.push_back(patternIdx);
                --sourceIdx;
                --patternIdx;
            }

            std::reverse(sourceIndices.begin(), sourceIndices.end());
            std::reverse(patternIndices.begin(), patternIndices.end());
        }
        return {sourceIndices, patternIndices};
    }

    template<class Painter>
    void CStepsExecutor<Painter>::initializeBadShiftTable()
    {
        const int patternSize = this->m_patternText.size();
        m_badShiftTable.reserve(SUPPORTED_ALPHABET.size());
        for(const auto& c : SUPPORTED_ALPHABET)
            m_badShiftTable[c] = patternSize;

        for(int i = 0; i < patternSize - 1; ++i)
            m_badShiftTable[this->m_patternText[i]] = patternSize - i - 1;
    }

    template<class Painter>
    void CStepsExecutor<Painter>::initializeGoodShiftTable()
    {
        const int patternSize = this->m_patternText.size();
        m_goodShiftTable.reserve(patternSize);
        const auto suffixes = calculateSuffixesForGoodShiftTable();

        for(int i = 0; i < patternSize; ++i)
            m_goodShiftTable.push_back(patternSize);

        int j = 0;
        for(int i = patternSize - 1; i >= 0; --i)
        {
            if(suffixes[i] == (i + 1))
                for(; j < patternSize - 1 - i; ++j)
                    if(m_goodShiftTable[j] == patternSize)
                        m_goodShiftTable[j] = patternSize - 1 - i;
        }

        for(int i = 0; i <= patternSize - 2; ++i)
            m_goodShiftTable[patternSize - 1 - suffixes[i]] = patternSize - 1 - i;
    }

    template<class Painter>
    std::vector<int> CStepsExecutor<Painter>::calculateSuffixesForGoodShiftTable() const
    {
        const int patternSize = this->m_patternText.size();
        std::vector<int> suffixes(patternSize);

        suffixes[patternSize - 1] = patternSize; // last char suffix is whole pattern
        int g = patternSize - 1, f = 0;

        for(int i = patternSize - 2; i>= 0; --i)
        {
            if((i > g) && (suffixes[i + patternSize - 1 - f] < i - g))
                suffixes[i] = suffixes[i + patternSize - 1 - f];
            else
            {
                if(i < g)
                    g = i;
                f = i;
                while((g >= 0) && (this->m_patternText[g] == this->m_patternText[g + patternSize - 1 - f]))
                    --g;
                suffixes[i] = f - g;
            }
        }
        return suffixes;
    }

    template class CStepsExecutor<Visualization::BoyerMoore::PainterPtr>;

} // BoyerMoore
} // Algorithms
