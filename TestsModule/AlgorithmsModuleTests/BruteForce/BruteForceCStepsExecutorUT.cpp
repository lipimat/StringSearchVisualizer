#include "TestCollector.h"

#include "../../AlgorithmsModule/BruteForce/IPainter.h"
#include "../../AlgorithmsModule/BruteForce/CStepsExecutor.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"

namespace Algorithms
{
namespace BruteForce
{

    using BruteForcePainter = Visualization::BruteForce::PainterPtr;
    using BruteForceStepsExecutor = CStepsExecutor<BruteForcePainter>;
    using namespace Steps;
    using BruteForceStep = StepPtr<BruteForcePainter>;
    using BruteForceComparisonStep = CComparison<BruteForcePainter>;
    using BruteForceMovePatternStep = CMovePattern<BruteForcePainter>;

    class BruteForceCStepsExecutorUT: public QObject
    {
        Q_OBJECT

    private:

        BruteForceStepsExecutor m_executor;

        void initializeExecutor(const std::string& source, const std::string& pattern)
        {
            m_executor.initialize({source, pattern});
        }

        template<class StepType>
        bool expectStep(const BruteForceStep& currentStep, const StepType& expectedStep)
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
            initializeExecutor("A", "AT");
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{});
        }

        void CalculateNextStepMatchedLetters()
        {
            initializeExecutor("A", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(currentStep, BruteForceComparisonStep(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{0});
        }

        void CalculateNextStepMismatchedLetters()
        {
            initializeExecutor("A", "T");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(currentStep, BruteForceComparisonStep(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));
        }

        void CalculateNextStepMatchedMissmatchedLetters()
        {
            initializeExecutor("AT", "AA");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(firstStep, BruteForceComparisonStep(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(secondStep, BruteForceComparisonStep(Indices{1}, Indices{1}, Steps::EComparisonType::MISMATCH)));
        }

        void CalculateNextStepPatternMismatchBufferShouldMove()
        {
            initializeExecutor("TA", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(firstStep, BruteForceComparisonStep(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceMovePatternStep>(secondStep, BruteForceMovePatternStep(1)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(thirdStep, BruteForceComparisonStep(Indices{1}, Indices{0}, Steps::EComparisonType::MATCH)));
        }

        void CalculateNextStepPatternFoundBufferShouldMove()
        {
            initializeExecutor("AT", "A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(firstStep, BruteForceComparisonStep(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();//nizej ruch
            QVERIFY(expectStep<BruteForceMovePatternStep>(secondStep, BruteForceMovePatternStep(1)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(thirdStep, BruteForceComparisonStep(Indices{1}, Indices{0}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
        }

        void CalculateNextStepCannotMoveBufferShouldFinish()
        {
            initializeExecutor("AAT", "ATC");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(firstStep, BruteForceComparisonStep(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<BruteForceComparisonStep>(secondStep, BruteForceComparisonStep(Indices{1}, Indices{1}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{});
        }
    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::BruteForceCStepsExecutorUT)
#include "BruteForceCStepsExecutorUT.moc"
