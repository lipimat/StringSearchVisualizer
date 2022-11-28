#include "TestCollector.h"

#include "../../AlgorithmsModule/Automaton/CStepsExecutor.h"

namespace Algorithms
{
namespace Automaton
{

    class AutomatonCStepsExecutorUT: public QObject
    {
        Q_OBJECT

    private:

        CStepsExecutor m_executor;

        void initializeExecutor(const std::string& source, const std::string& pattern)
        {
            m_executor.initialize({source, pattern});
        }

        template<class StepType>
        bool expectStep(const Steps::StepPtr& currentStep, const StepType& expectedStep)
        {
            auto ret = false;
            const auto& castedStep = dynamic_cast<StepType*>(currentStep.get());
            if(castedStep != nullptr)
                ret = (*castedStep == expectedStep);
            return ret;
        }

    private slots:

    };

} //Automaton
} //Algorithms

ADD_TEST(Algorithms::Automaton::AutomatonCStepsExecutorUT)
#include "AutomatonCStepsExecutorUT.moc"
