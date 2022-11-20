#include "TestCollector.h"

#include "../../AlgorithmsModule/BruteForce/CStepsExecutor.h"

#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"
#include "qtestcase.h"

namespace Algorithms
{
namespace BruteForce
{

    using namespace Steps;

    class CStepsExecutorUT: public QObject
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

        void CalculateNextStepPatternLongerThanSourceShouldFinish()
        {
            initializeExecutor("A", "AB");
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{});
        }

        void CalculateNextStepMatchedLetters()
        {
            initializeExecutor("A", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(currentStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{0});
        }

        void CalculateNextStepMismatchedLetters()
        {
            initializeExecutor("A", "B");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(currentStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));
        }

        void CalculateNextStepMatchedMissmatchedLetters()
        {
            initializeExecutor("AB", "AA");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(secondStep, CComparison(Indices{1}, Indices{1}, Steps::EComparisonType::MISMATCH)));
        }

        void CalculateNextStepPatternMismatchBufferShouldMove()
        {
            initializeExecutor("BA", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CMovePattern>(secondStep, CMovePattern()));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(thirdStep, CComparison(Indices{1}, Indices{0}, Steps::EComparisonType::MATCH)));
        }

        void CalculateNextStepPatternFoundBufferShouldMove()
        {
            initializeExecutor("AB", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();//nizej ruch
            QVERIFY(expectStep<CMovePattern>(secondStep, CMovePattern()));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(thirdStep, CComparison(Indices{1}, Indices{0}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
        }

        void CalculateNextStepCannotMoveBufferShouldFinish()
        {
            initializeExecutor("AAB", "ABC");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(secondStep, CComparison(Indices{1}, Indices{1}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{});
        }
    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::CStepsExecutorUT)
#include "CStepsExecutorUT.moc"
