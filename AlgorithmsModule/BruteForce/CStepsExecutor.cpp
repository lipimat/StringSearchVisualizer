#include "assert.h"
#include "CStepsExecutor.h"

#include "../Steps/CTrueComparison.h"
#include "../Steps/CFalseComparison.h"

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
    }

    Steps::EState CStepsExecutor::calculateNextStep()
    {
        const auto patternSize = m_patternText.size();
        const auto sourceSize = m_sourceText.size();

        const auto patternCannotFitIntoRemainingSource = patternSize > (sourceSize - m_currentSourceIndex);
        if(patternCannotFitIntoRemainingSource)
            return Steps::EState::FINISHED;

        const auto isCurrentPatternIndexInBound = m_currentPatternIndex <= (patternSize - 1);
        const auto isCurrentSourceIndexInBound = (m_currentSourceIndex + m_currentPatternIndex) <= (sourceSize - 1);
        assert(isCurrentPatternIndexInBound);
        assert(isCurrentSourceIndexInBound);

        if(m_patternText[m_currentPatternIndex] == m_sourceText[m_currentSourceIndex + m_currentPatternIndex])
        {
            m_currentStep = std::make_unique<Steps::CTrueComparison>();
            m_currentPatternIndex++;
            if(m_currentPatternIndex == m_patternText.size()) //out of bounds, we loop
            {
                m_currentPatternIndex = 0;
                m_currentSourceIndex++;
            }
        }
        else
        {
            m_currentPatternIndex = 0;
            m_currentSourceIndex++;
            m_currentStep = std::make_unique<Steps::CFalseComparison>();
        }

        return Steps::EState::CONTINUE;
    }

    const Steps::StepPtr& CStepsExecutor::getCurrentStep() const
    {
        return m_currentStep;
    }

} //BruteForce
} //Algorithms
