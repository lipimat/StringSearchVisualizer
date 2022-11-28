#include "TestCollector.h"

#include "../../AlgorithmsModule/BoyerMoore/CStepsExecutor.h"
#include "../../AlgorithmsModule/Steps/CComparison.h"
#include "../../AlgorithmsModule/Steps/CMovePattern.h"

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
            QVERIFY(expectStep<CComparison>(currentStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::FINISHED);
            QCOMPARE(m_executor.getFoundPatternIndices(), Indices{0});
        }

        void CalculateNextStepMismatchedLetters()
        {
            initializeExecutor("A", "T");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& currentStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(currentStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));
        }

        void CalculateNextStepMatchedMissmatchedLettersMatchingFromPatternBack()
        {
            initializeExecutor("TA", "AA");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{1}, Indices{1}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(secondStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));
        }

        void CalculateNextStepGoodShiftPatternInsideReoccurs()
        {
            initializeExecutor("TCCATAGGGG", "GTACTA");
            //we should move to allign TA
            //after move we should have
            //TCCATAGGGG
            //   GTACTA
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{5}, Indices{5}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(secondStep, CComparison(Indices{4}, Indices{4}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(thirdStep, CComparison(Indices{3}, Indices{3}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& analyzeShiftStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(analyzeShiftStep, CComparison(Indices{4, 5}, Indices{1, 2}, Steps::EComparisonType::IDLE)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& moveStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CMovePattern>(moveStep, CMovePattern(3)));
        }

        void CalculateNextStepGoodShiftInsidePatternReoccursOnlySuffix()
        {
            initializeExecutor("TGTAGGG", "ACTA");
            //we should move to allign BA
            //after move we should have
            //TGTAGGG
            //   ACTA

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{3}, Indices{3}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(secondStep, CComparison(Indices{2}, Indices{2}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(thirdStep, CComparison(Indices{1}, Indices{1}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& analyzeShiftStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(analyzeShiftStep, CComparison(Indices{3}, Indices{0}, Steps::EComparisonType::IDLE)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& moveStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CMovePattern>(moveStep, CMovePattern(3)));
        }

        void CalculateNextStepBadShiftAllignCharacter()
        {
            initializeExecutor("TCGCA", "GACG");
            //we should move to allign to C
            //after move we should have
            //TCGCA
            // GACG

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{3}, Indices{3}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& analyzeShiftStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(analyzeShiftStep, CComparison(Indices{3}, Indices{2}, Steps::EComparisonType::IDLE)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& moveStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CMovePattern>(moveStep, CMovePattern(1)));
        }

        void CalculateNextStepBadShiftCannotAllignCharacter()
        {
            initializeExecutor("TGATAA", "CGA");
            //we should move whole pattern
            //after move we should have
            //TTGATAA
            //   CGA

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(firstStep, CComparison(Indices{2}, Indices{2}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(secondStep, CComparison(Indices{1}, Indices{1}, Steps::EComparisonType::MATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& thirdStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(thirdStep, CComparison(Indices{0}, Indices{0}, Steps::EComparisonType::MISMATCH)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& analyzeShiftStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CComparison>(analyzeShiftStep, CComparison(Indices{}, Indices{0,1,2}, Steps::EComparisonType::IDLE)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& moveStep = m_executor.getCurrentStep();
            QVERIFY(expectStep<CMovePattern>(moveStep, CMovePattern(3)));
        }

    };

} //BoyerMoore
} //Algorithms

ADD_TEST(Algorithms::BoyerMoore::BoyerMooreCStepsExecutorUT)
#include "BoyerMooreCStepsExecutorUT.moc"
