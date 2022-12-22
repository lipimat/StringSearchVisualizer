#include "CStepsExecutor.h"
#include "IPainter.h"
#include "../Steps/CComparison.h"
#include "../Steps/CMovePattern.h"

namespace Algorithms
{
namespace BruteForce
{

    template<class Painter>
    void CStepsExecutor<Painter>::initialize(const TextsPair& texts)
    {
        m_sourceText = texts.first;
        m_patternText = texts.second;
        m_currentPatternIndex = 0;
        m_currentSourceIndex = 0;
        m_shouldMovePattern = false;
        m_steps.clear();
        m_patternFound.clear();
    }

    template<class Painter>
    Steps::EAlgorithmState CStepsExecutor<Painter>::calculateNextStep()
    {
        auto returnState = Steps::EAlgorithmState::CONTINUE;

        if(patternWontFitToRemainingSource())
            returnState = Steps::EAlgorithmState::FINISHED;
        else if(m_shouldMovePattern)
        {
            m_shouldMovePattern = false;
            m_steps.push_back(std::make_unique<Steps::CMovePattern<Painter>>(1));
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
            m_steps.push_back(std::make_unique<Steps::CComparison<Painter>>
                              (Steps::Indices{comparisonSourceIndex}, Steps::Indices{comparisonPatternIndex}, comparisonType));
        }

        return returnState;
    }

    template<class Painter>
    void CStepsExecutor<Painter>::updateMembersForPatternMove()
    {
        m_currentPatternIndex = 0;
        m_currentSourceIndex++;
        m_shouldMovePattern = true;
    }

    template<class Painter>
    void CStepsExecutor<Painter>::fillFoundPatternIndices(const int start)
    {
        const auto stop = start + m_patternText.size();
        for(auto i = start; i < stop; ++i)
            m_patternFound.push_back(i);
    }

    template<class Painter>
    bool CStepsExecutor<Painter>::patternWontFitToRemainingSource()
    {
        const int spaceLeft = m_sourceText.size() - m_currentSourceIndex; //to avoid overlflow and cast to ull
        return m_patternText.size() > spaceLeft;
    }

    template<class Painter>
    const Steps::StepPtr<Painter>& CStepsExecutor<Painter>::getCurrentStep() const
    {
        return m_steps.back();
    }

    template<class Painter>
    const Steps::Indices& CStepsExecutor<Painter>::getFoundPatternIndices() const
    {
        return m_patternFound;
    }

    template class CStepsExecutor<Visualization::BruteForce::PainterPtr>;

} // BruteForce
} // Algorithms
