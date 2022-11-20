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
        const auto patternSize = m_patternText.size();
        const auto sourceSize = m_sourceText.size();

        const auto patternCannotFitIntoRemainingSource = patternSize > (sourceSize - m_currentSourceIndex);
        if(patternCannotFitIntoRemainingSource)
            return Steps::EAlgorithmState::FINISHED;

        if(m_shouldMovePattern) //out of bounds or fail we loop
        {
            m_shouldMovePattern = false;
            m_steps.push_back(std::make_unique<Steps::CMovePattern>());
            return Steps::EAlgorithmState::CONTINUE;
        }

        const auto isCurrentPatternIndexInBound = m_currentPatternIndex <= (patternSize - 1);
        const auto isCurrentSourceIndexInBound = (m_currentSourceIndex + m_currentPatternIndex) <= (sourceSize - 1);
        assert(isCurrentPatternIndexInBound);
        assert(isCurrentSourceIndexInBound);

        const auto& sourceComparisonIndices = Steps::Indices{m_currentSourceIndex + m_currentPatternIndex};
        const auto& patternComparisonIndices = Steps::Indices{m_currentPatternIndex};

        if(m_patternText[m_currentPatternIndex] == m_sourceText[m_currentSourceIndex + m_currentPatternIndex])
        {
            m_steps.push_back(std::make_unique<Steps::CComparison>
                              (sourceComparisonIndices, patternComparisonIndices, Steps::EComparisonType::MATCH));
            m_currentPatternIndex++;
            if(m_currentPatternIndex == m_patternText.size()) //out of bounds, we loop
            {
                fillFoundPatternIndices(m_currentSourceIndex);
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
            m_steps.push_back(std::make_unique<Steps::CComparison>
                              (sourceComparisonIndices, patternComparisonIndices, Steps::EComparisonType::MISMATCH));
        }

        return Steps::EAlgorithmState::CONTINUE;
    }

    void CStepsExecutor::fillFoundPatternIndices(const int start)
    {
        const auto stop = start + m_patternText.size();
        for(auto i = start; i < stop; ++i)
            m_patternFound.push_back(i);
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
