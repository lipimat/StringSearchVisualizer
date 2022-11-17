#include "assert.h"
#include "CStepsExecutor.h"

#include "Steps/CTrueComparison.h"
#include "Steps/CFalseComparison.h"
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
    }

    Steps::EState CStepsExecutor::calculateNextStep()
    {
        const auto patternSize = m_patternText.size();
        const auto sourceSize = m_sourceText.size();

        const auto patternCannotFitIntoRemainingSource = patternSize > (sourceSize - m_currentSourceIndex);
        if(patternCannotFitIntoRemainingSource)
            return Steps::EState::FINISHED;

        if(m_shouldMovePattern) //out of bounds or fail we loop
        {
            m_shouldMovePattern = false;
            m_steps.push_back(std::make_unique<Steps::CMovePattern>());
            return Steps::EState::CONTINUE;
        }

        const auto isCurrentPatternIndexInBound = m_currentPatternIndex <= (patternSize - 1);
        const auto isCurrentSourceIndexInBound = (m_currentSourceIndex + m_currentPatternIndex) <= (sourceSize - 1);
        assert(isCurrentPatternIndexInBound);
        assert(isCurrentSourceIndexInBound);

        const auto& sourceComparisonIndices = Steps::Indices{m_currentSourceIndex + m_currentPatternIndex};
        const auto& patternComparisonIndices = Steps::Indices{m_currentPatternIndex};

        if(m_patternText[m_currentPatternIndex] == m_sourceText[m_currentSourceIndex + m_currentPatternIndex])
        {
            m_steps.push_back(std::make_unique<Steps::CTrueComparison>(sourceComparisonIndices, patternComparisonIndices));
            m_currentPatternIndex++;
            if(m_currentPatternIndex == m_patternText.size()) //out of bounds, we loop
            {
                m_currentPatternIndex = 0;
                m_currentSourceIndex++;
                m_shouldMovePattern = true;
            }
        }
        else
        { 
            m_currentPatternIndex = 0;
            m_currentSourceIndex++;
            m_shouldMovePattern = true;
            m_steps.push_back(std::make_unique<Steps::CFalseComparison>(sourceComparisonIndices, patternComparisonIndices));
        }

        return Steps::EState::CONTINUE;
    }

    const Steps::StepPtr& CStepsExecutor::getCurrentStep() const
    {
        return m_steps.back();
    }

} //BruteForce
} //Algorithms
