#pragma once

#include "IStepsExecutor.h"
#include "Steps/IStep.h"

namespace Algorithms
{

    template<class Painter>
    class ABaseStepsExecutor : public IStepsExecutor<Painter>
    {
    public:

        void initialize(const TextsPair& texts) override
        {
            m_sourceText = texts.first;
            m_patternText = texts.second;
            m_patternFound.clear();
            m_steps.clear();
        };
        const Steps::StepPtr<Painter>& getCurrentStep() const override { return m_steps.back(); };
        const Steps::Indices& getFoundPatternIndices() const override { return m_patternFound; };

    protected:

        void fillFoundPatternIndices(const int start)
        {
            const int stop = start + m_patternText.size();
            for(int i = start; i < stop; ++i)
                m_patternFound.push_back(i);
        };

        std::string m_sourceText;
        std::string m_patternText;
        Steps::Indices m_patternFound;
        std::vector<Steps::StepPtr<Painter>> m_steps;
    };

} // Algorithms
