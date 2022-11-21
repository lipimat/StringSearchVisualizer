#include "TestCollector.h"

#include "../../AlgorithmsModule/BoyerMoore/CStepsExecutor.h"
#include "qtestcase.h"

namespace Algorithms
{
namespace BoyerMoore
{

    using namespace Steps;

    class BoyerMooreCStepsExecutorUT: public QObject
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

        void InitializeBadCharacterShiftTableWithPatternLength()
        {

        }
    };

} //BoyerMoore
} //Algorithms

ADD_TEST(Algorithms::BoyerMoore::BoyerMooreCStepsExecutorUT)
#include "BoyerMooreCStepsExecutorUT.moc"
