#pragma once

#include "IStepsExecutor.h"

#include "../Steps/Constants.h"

namespace Algorithms
{
namespace Automaton
{

    class CStepsExecutor final : public IStepsExecutor
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;
        const Steps::StepPtr& getCurrentStep() const override;
        const Visualization::Indices& getFoundPatternIndices() const override;

    private:

        void fillFoundPatternIndices(const int /*start*/);

        void computeAutomaton();
        int getNextState(const char /*alphabetLetter*/) const;
        std::vector< std::unordered_map<char, int> > m_automaton;
        bool m_generatingAutomatonStage;
        int m_currentStateNr;

        bool m_comparisonStage;
        int m_currentSourceIndex;
        std::string m_sourceText;
        std::string m_patternText;
        Visualization::Indices m_patternFound;
        std::vector<Steps::StepPtr> m_steps;
    };

} //BoyerMoore
} //Algorithms
