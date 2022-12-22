#pragma once

#include "../IStepsExecutor.h"
#include "../Steps/IStep.h"

namespace Algorithms
{
namespace Automaton
{

    template<class Painter>
    class CStepsExecutor final : public IStepsExecutor<Painter>
    {
    public:

        void initialize(const TextsPair&) override;
        Steps::EAlgorithmState calculateNextStep() override;
        const Steps::StepPtr<Painter>& getCurrentStep() const override;
        const Steps::Indices& getFoundPatternIndices() const override;

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
        Steps::Indices m_patternFound;
        std::vector<Steps::StepPtr<Painter>> m_steps;
    };

} // Automaton
} // Algorithms
