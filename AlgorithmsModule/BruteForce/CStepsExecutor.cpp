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
        ABaseStepsExecutor<Painter>::initialize(texts);
        m_currentPatternIndex = 0;
        m_currentSourceIndex = 0;
        m_shouldMovePattern = false;
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
            this->m_steps.push_back(std::make_unique<Steps::CMovePattern<Painter>>(1));
        }
        else
        {
            const auto patternSize = this->m_patternText.size();
            const auto sourceSize = this->m_sourceText.size();

            const auto comparisonSourceIndex = m_currentSourceIndex + m_currentPatternIndex;
            const auto comparisonPatternIndex = m_currentPatternIndex;

            const auto isCurrentSourceIndexInBound = comparisonSourceIndex <= (sourceSize - 1);
            const auto isCurrentPatternIndexInBound = comparisonPatternIndex <= (patternSize - 1);
            assert(isCurrentSourceIndexInBound);
            assert(isCurrentPatternIndexInBound);

            Steps::EComparisonType comparisonType;
            if(this->m_patternText[comparisonPatternIndex] == this->m_sourceText[comparisonSourceIndex])
            {
                comparisonType = Steps::EComparisonType::MATCH;
                m_currentPatternIndex++;
                if(m_currentPatternIndex == this->m_patternText.size()) //out of bounds, we loop
                {
                    this->fillFoundPatternIndices(m_currentSourceIndex);
                    updateMembersForPatternMove();
                }
            }
            else
            {
                updateMembersForPatternMove();
                comparisonType = Steps::EComparisonType::MISMATCH;
            }
            this->m_steps.push_back(std::make_unique<Steps::CComparison<Painter>>
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
    bool CStepsExecutor<Painter>::patternWontFitToRemainingSource()
    {
        const int spaceLeft = this->m_sourceText.size() - m_currentSourceIndex; //to avoid overlflow and cast to ull
        return this->m_patternText.size() > spaceLeft;
    }

    template class CStepsExecutor<Visualization::BruteForce::PainterPtr>;

} // BruteForce
} // Algorithms
