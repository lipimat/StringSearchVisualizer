#include "CStepsExecutor.h"

#include "../SupportedAlgorithmsToolsets.h"
#include "../Steps/CComparison.h"
#include "../Steps/CMovePattern.h"

namespace Algorithms
{
namespace BoyerMoore
{

    void CStepsExecutor::initialize(const TextsPair& texts)
    {
        m_sourceText = texts.first;
        m_patternText = texts.second;
        m_currentPatternIndex = m_patternText.size() - 1; // we start from end of pattern
        m_currentSourceIndex = 0;
        m_patternLastMovedBy = 0;
        m_shouldMovePattern = false;
        m_analyzeNextShift = false;
        m_steps.clear();
        m_patternFound.clear();
        m_badShiftTable.clear();
        m_goodShiftTable.clear();

        initializeBadShiftTable();
        initializeGoodShiftTable();
    }

    Steps::EAlgorithmState CStepsExecutor::calculateNextStep()
    {
        auto returnState = Steps::EAlgorithmState::CONTINUE;

        if(patternWontFitIntoRemainingSource())
            returnState = Steps::EAlgorithmState::FINISHED;
        else if(m_shouldMovePattern)
        {
            m_shouldMovePattern = false;
            m_steps.push_back(std::make_unique<Steps::CMovePattern>(m_patternLastMovedBy));
            m_patternLastMovedBy = 0;
        }
        else if(m_analyzeNextShift)
        {
            m_analyzeNextShift = false;
            const int goodShiftMove = m_goodShiftTable[m_currentPatternIndex];
            const int badShiftMove = m_badShiftTable[m_sourceText[m_currentPatternIndex + m_currentSourceIndex]] -
                    m_patternText.size() + 1 + m_currentPatternIndex;
            int shouldMoveBy = 0;
            std::pair<Steps::Indices, Steps::Indices> indices;
            if(goodShiftMove > badShiftMove)
            {
                shouldMoveBy = goodShiftMove;
                indices = calculateGoodShiftPreMoveIndices(shouldMoveBy);
            }
            else
            {
                shouldMoveBy = badShiftMove;
                if(shouldMoveBy != m_patternText.size()) // allign to specific character
                {
                    indices.first.push_back(m_currentSourceIndex + m_currentPatternIndex);
                    indices.second.push_back(m_patternText.size() - shouldMoveBy - 1);
                }
            }
            if(indices.first.empty() && indices.second.empty()) //couldnt resolve anything, will move by whole pattern
            {
                indices.first.clear();
                for(int i = 0; i < m_patternText.size(); ++i)
                    indices.second.push_back(i);
            }
            m_steps.push_back(std::make_unique<Steps::CComparison>
                              (indices.first, indices.second, Steps::EComparisonType::IDLE));
            updateMembersForPatternMove(shouldMoveBy);
        }
        else
        {
            const auto comparisonSourceIndex = m_currentSourceIndex + m_currentPatternIndex;
            const auto comparisonPatternIndex = m_currentPatternIndex;

            const auto isCurrentSourceIndexInBound = comparisonSourceIndex <= (m_sourceText.size() - 1);
            const auto isCurrentPatternIndexInBound = comparisonPatternIndex >= 0;
            assert(isCurrentSourceIndexInBound);
            assert(isCurrentPatternIndexInBound);

            Steps::EComparisonType comparisonType;
            if(m_patternText[comparisonPatternIndex] == m_sourceText[comparisonSourceIndex])
            {
                comparisonType = Steps::EComparisonType::MATCH;
                m_currentPatternIndex--;
                if(m_currentPatternIndex < 0) //out of bounds, we loop
                {
                    fillFoundPatternIndices(m_currentSourceIndex);
                    updateMembersForPatternMove(m_patternText.size());
                }
            }
            else
            {
                m_analyzeNextShift = true;
                comparisonType = Steps::EComparisonType::MISMATCH;
            }
            m_steps.push_back(std::make_unique<Steps::CComparison>
                              (Steps::Indices{comparisonSourceIndex}, Steps::Indices{comparisonPatternIndex}, comparisonType));
        }

        return returnState;
    }

    const Steps::StepPtr& CStepsExecutor::getCurrentStep() const
    {
        return m_steps.back();
    }

    const Visualization::Indices& CStepsExecutor::getFoundPatternIndices() const
    {
        return m_patternFound;
    }

    void CStepsExecutor::updateMembersForPatternMove(const int moveBy)
    {
        m_currentPatternIndex = m_patternText.size() - 1;
        m_currentSourceIndex += moveBy;
        m_patternLastMovedBy = moveBy;
        m_shouldMovePattern = true;
    }

    void CStepsExecutor::fillFoundPatternIndices(const int start)
    {
        const int stop = start + m_patternText.size();
        for(int i = start; i < stop; ++i)
            m_patternFound.push_back(i);
    }

    bool CStepsExecutor::patternWontFitIntoRemainingSource() const
    {
        const int spaceLeft = m_sourceText.size() - m_patternText.size(); //to avoid overflow and cast to ull
        return m_currentSourceIndex > spaceLeft;
    }

    std::pair<Visualization::Indices, Visualization::Indices> CStepsExecutor::calculateGoodShiftPreMoveIndices
        (const int moveBy) const
    {
        Visualization::Indices sourceIndices, patternIndices;
        const int comparedBeforeMiss = m_patternText.size() - m_currentPatternIndex - 1;

        int sourceIdx = m_currentSourceIndex + m_patternText.size() - 1;
        int patternIdx = sourceIdx - moveBy;
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
        return {sourceIndices, patternIndices};
    }

    void CStepsExecutor::initializeBadShiftTable()
    {
        const int patternSize = m_patternText.size();
        m_badShiftTable.reserve(SUPPORTED_ALPHABET.size());
        for(const auto& c : SUPPORTED_ALPHABET)
            m_badShiftTable[c] = patternSize;

        for(int i = 0; i < patternSize - 1; ++i)
            m_badShiftTable[m_patternText[i]] = patternSize - i - 1;
    }

    void CStepsExecutor::initializeGoodShiftTable()
    {
        const int patternSize = m_patternText.size();
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

    std::vector<int> CStepsExecutor::calculateSuffixesForGoodShiftTable() const
    {
        const int patternSize = m_patternText.size();
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
                while((g >= 0) && (m_patternText[g] == m_patternText[g + patternSize - 1 - f]))
                    --g;
                suffixes[i] = f - g;
            }
        }
        return suffixes;
    }

} //BoyerMoore
} //Algorithms
