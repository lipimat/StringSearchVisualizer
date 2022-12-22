#pragma once

#include "../ABaseStepsExecutor.h"

namespace Algorithms
{
namespace Automaton
{

    template<class Painter>
    class CStepsExecutor final : public ABaseStepsExecutor<Painter>
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;

    private:

        void computeAutomaton();
        int getNextState(const char /*alphabetLetter*/) const;

        std::vector< std::unordered_map<char, int> > m_automaton;
        bool m_generatingAutomatonStage;
        bool m_comparisonStage;
        int m_currentStateNr;
        int m_currentSourceIndex;
    };

} // Automaton
} // Algorithms
