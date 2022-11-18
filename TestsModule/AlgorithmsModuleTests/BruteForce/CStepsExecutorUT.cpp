#include "TestCollector.h"

#include "../../AlgorithmsModule/BruteForce/CStepsExecutor.h"

#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"

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

    private slots:

        void CalculateNextStepPatternLongerThanSourceShouldFinish()
        {
            initializeExecutor("A", "AB");
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
        }

        void CalculateNextStepMatchedLetters()
        {
            initializeExecutor("A", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(currentStep.get()) != nullptr);
        }

        void CalculateNextStepMismatchedLetters()
        {
            initializeExecutor("A", "B");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(currentStep.get()) != nullptr);
        }

        void CalculateNextStepMatchedMissmatchedLetters()
        {
            initializeExecutor("AB", "AA");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(firstStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(secondStep.get()) != nullptr);
        }

        void CalculateNextStepPatternMismatchBufferShouldMove()
        {
            initializeExecutor("BA", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(firstStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CMovePattern*>(secondStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(thirdStep.get()) != nullptr);
        }

        void CalculateNextStepPatternFoundBufferShouldMove()
        {
            initializeExecutor("AB", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(firstStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CMovePattern*>(secondStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(thirdStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
        }

        void CalculateNextStepCannotMoveBufferShouldFinish()
        {
            initializeExecutor("AAB", "ABC");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(firstStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(dynamic_cast<CComparison*>(secondStep.get()) != nullptr);

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
        }
    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::CStepsExecutorUT)
#include "CStepsExecutorUT.moc"
