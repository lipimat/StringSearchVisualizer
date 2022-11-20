#include "assert.h"
#include "CStepsExecutor.h"

#include "Steps/CComparison.h"
#include "Steps/CMovePattern.h"

namespace Algorithms
{
namespace BruteForce
{

    void CStepsExecutor::initialize(const TextsPair& texts)
    {
        m_sourceText = texts.first;
        m_patternText = texts.second;
        m_currentPatternIndex = 0;
        m_currentSourceIndex = 0;
        m_shouldMovePattern = false;
        m_steps.clear();
        m_patternFound.clear();
    }

    Steps::EAlgorithmState CStepsExecutor::calculateNextStep()
    {
        auto returnState = Steps::EAlgorithmState::CONTINUE;

        if(patternWontFitToRemainingSource())
            returnState = Steps::EAlgorithmState::FINISHED;
        else if(m_shouldMovePattern)
        {
            m_shouldMovePattern = false;
            m_steps.push_back(std::make_unique<Steps::CMovePattern>());
        }
        else
        {
            const auto patternSize = m_patternText.size();
            const auto sourceSize = m_sourceText.size();

            const auto comparisonSourceIndex = m_currentSourceIndex + m_currentPatternIndex;
            const auto comparisonPatternIndex = m_currentPatternIndex;

            const auto isCurrentSourceIndexInBound = comparisonSourceIndex <= (sourceSize - 1);
            const auto isCurrentPatternIndexInBound = comparisonPatternIndex <= (patternSize - 1);
            assert(isCurrentSourceIndexInBound);
            assert(isCurrentPatternIndexInBound);

            Steps::EComparisonType comparisonType;
            if(m_patternText[comparisonPatternIndex] == m_sourceText[comparisonSourceIndex])
            {
                comparisonType = Steps::EComparisonType::MATCH;
                m_currentPatternIndex++;
                if(m_currentPatternIndex == m_patternText.size()) //out of bounds, we loop
                {
                    fillFoundPatternIndices(m_currentSourceIndex);
                    updateMembersForPatternMove();
                }
            }
            else
            {
                updateMembersForPatternMove();
                comparisonType = Steps::EComparisonType::MISMATCH;
            }
            m_steps.push_back(std::make_unique<Steps::CComparison>
                              (Steps::Indices{comparisonSourceIndex}, Steps::Indices{comparisonPatternIndex}, comparisonType));
        }

        return returnState;
    }

    void CStepsExecutor::updateMembersForPatternMove()
    {
        m_currentPatternIndex = 0;
        m_currentSourceIndex++;
        m_shouldMovePattern = true;
    }

    void CStepsExecutor::fillFoundPatternIndices(const int start)
    {
        const auto stop = start + m_patternText.size();
        for(auto i = start; i < stop; ++i)
            m_patternFound.push_back(i);
    }

    bool CStepsExecutor::patternWontFitToRemainingSource()
    {
        return m_patternText.size() > (m_sourceText.size() - m_currentSourceIndex);
    }

    const Steps::StepPtr& CStepsExecutor::getCurrentStep() const
    {
        return m_steps.back();
    }

    const Visualization::Indices& CStepsExecutor::getFoundPatternIndices() const
    {
        return m_patternFound;
    }

} //BruteForce
} //Algorithms
