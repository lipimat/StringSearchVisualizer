#include "CStepsExecutor.h"
#include "IPainter.h"
#include "../SupportedAlgorithmsAlphabet.h"
#include "../Steps/CDrawAutomatonNode.h"
#include "../Steps/CStartAutomaton.h"
#include "../Steps/CStateChangedAutomaton.h"

namespace Algorithms
{
namespace Automaton
{

    template<class Painter>
    void CStepsExecutor<Painter>::initialize(const TextsPair& texts)
    {
        m_sourceText = texts.first;
        m_patternText = texts.second;
        m_generatingAutomatonStage = true;
        m_comparisonStage = false;
        m_currentStateNr = 0;
        m_currentSourceIndex = 0;
        m_automaton.clear();
        m_automaton.reserve(m_patternText.size() + 1);
        m_steps.clear();
        m_patternFound.clear();
    }

    template<class Painter>
    Steps::EAlgorithmState CStepsExecutor<Painter>::calculateNextStep()
    {
        auto returnState = Steps::EAlgorithmState::CONTINUE;

        if(m_generatingAutomatonStage)
            computeAutomaton();
        else if(m_comparisonStage)
        {
            const auto& sourceSize = m_sourceText.size();
            if(m_currentSourceIndex >= sourceSize)
                returnState = Steps::EAlgorithmState::FINISHED;
            else
            {
                assert(m_currentStateNr >= 0 && m_currentStateNr <= m_automaton.size());
                auto& mapForState = m_automaton[m_currentStateNr];
                m_currentStateNr = mapForState[m_sourceText[m_currentSourceIndex]];

                if(m_currentStateNr == m_patternText.size())
                    fillFoundPatternIndices(m_currentSourceIndex - m_patternText.size() + 1);

                m_steps.push_back(std::make_unique<Steps::CStateChangedAutomaton<Painter>>
                                  (Steps::Indices{m_currentSourceIndex}, m_currentStateNr));
                m_currentSourceIndex++;
            }
        }

        return returnState;
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

    template<class Painter>
    void CStepsExecutor<Painter>::fillFoundPatternIndices(const int start)
    {
        const int stop = start + m_patternText.size();
        for(int i = start; i < stop; ++i)
            m_patternFound.push_back(i);
    }

    template<class Painter>
    void CStepsExecutor<Painter>::computeAutomaton()
    {
        const int patternSize = m_patternText.size();
        if(m_currentStateNr > patternSize)
        {
            m_generatingAutomatonStage = false;
            m_comparisonStage = true;
            m_currentStateNr = 0;
            // we will reuse m_currentStateNr
            m_steps.push_back(std::make_unique<Steps::CStartAutomaton<Painter>>());
        }
        else
        {
            std::unordered_map<char, int> tempMap;
            Steps::NodeRelations relations;
            for(const auto& c : SUPPORTED_ALPHABET)
            {
                 tempMap[c] = getNextState(c);
                 if(tempMap[c] != 0)
                     relations.push_back({tempMap[c],c});
            }
            m_automaton.push_back(tempMap);
            m_steps.push_back(std::make_unique<Steps::CDrawAutomatonNode<Painter>>(m_currentStateNr, relations));
            m_currentStateNr++;
        }
    }

    template<class Painter>
    int CStepsExecutor<Painter>::getNextState(const char alphabetLetter) const
    {
        // if this letter is the same as next in pattern we just move state up
        if(m_currentStateNr < m_patternText.size() && alphabetLetter == m_patternText[m_currentStateNr])
            return m_currentStateNr + 1;

        int nextState, i;
        for(nextState = m_currentStateNr; nextState > 0; --nextState)
        {
            if(m_patternText[nextState - 1] == alphabetLetter)
            {
                for(i = 0; i < nextState - 1; ++i)
                    if(m_patternText[i] != m_patternText[m_currentStateNr - nextState + 1 + i])
                        break;
                if(i == nextState - 1)
                    return nextState;
            }
        }

        return 0;
    }

    template class CStepsExecutor<Visualization::Automaton::PainterPtr>;

} // Automaton
} // Algorithms
