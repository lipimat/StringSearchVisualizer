#include "TestCollector.h"

#include "../../AlgorithmsModule/Automaton/IPainter.h"
#include "../../AlgorithmsModule/Automaton/CStepsExecutor.h"
#include "../../AlgorithmsModule/Steps/CDrawAutomatonNode.h"
#include "../../AlgorithmsModule/Steps/Constants.h"

namespace Algorithms
{
namespace Automaton
{

    using AutomatonPainter = Visualization::Automaton::PainterPtr;
    using AutomatonStepsExecutor = CStepsExecutor<AutomatonPainter>;
    using namespace Steps;
    using AutomatonStep = StepPtr<AutomatonPainter>;
    using AutomatonDrawNodeStep = CDrawAutomatonNode<AutomatonPainter>;

    // I'm only testing creating the automaton
    // I don't see any need to test iteration over created automaton, important thing is that it should be created correctly
    class AutomatonCStepsExecutorUT: public QObject
    {
        Q_OBJECT

    private:

        AutomatonStepsExecutor m_executor;

        void initializeExecutor(const std::string& source, const std::string& pattern)
        {
            m_executor.initialize({source, pattern});
        }

        template<class StepType>
        bool expectStep(const AutomatonStep& currentStep, const StepType& expectedStep)
        {
            auto ret = false;
            const auto& castedStep = dynamic_cast<StepType*>(currentStep.get());
            if(castedStep != nullptr)
                ret = (*castedStep == expectedStep);
            return ret;
        }

    private slots:

        void AutomatonProperVertexFrom0to1AndFrom1to1SingleVertices()
        {
            initializeExecutor("A","A");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& firstStep = m_executor.getCurrentStep();

            NodeRelations state0relations {
                {1, 'A'}
            };
            //that means I expect vertex from created node to 1 with 'A' label
            //  A
            //0 -> 1
            QVERIFY(expectStep<AutomatonDrawNodeStep>(firstStep, AutomatonDrawNodeStep(0, state0relations)));

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            const auto& secondStep = m_executor.getCurrentStep();

            //that means I expect vertex from created node to 1 with 'A' label
            //  A
            //1 -> 1
            QVERIFY(expectStep<AutomatonDrawNodeStep>(secondStep, AutomatonDrawNodeStep(1, state0relations)));
        }

        void AutomatonProperVerticesFrom3rdStateMultipleVertices2()
        {
            initializeExecutor("A","ACAC");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);

            const auto& thirdStep = m_executor.getCurrentStep();
            //find a way to sort relations in this step, right now go with alphabet order
            NodeRelations state3relations {
                {1, 'A'},
                {4, 'C'}
            };
            QVERIFY(expectStep<AutomatonDrawNodeStep>(thirdStep, AutomatonDrawNodeStep(3, state3relations)));
        }

        void AutomatonProperVerticesFrom5thStateMultipleVertices3()
        {
            initializeExecutor("A","ACACAG");

            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);
            QCOMPARE(m_executor.calculateNextStep(), EAlgorithmState::CONTINUE);

            const auto& fithStep = m_executor.getCurrentStep();
            //find a way to sort relations in this step, right now go with alphabet order
            NodeRelations state5relations {
                {1, 'A'},
                {4, 'C'},
                {6, 'G'}
            };
            QVERIFY(expectStep<AutomatonDrawNodeStep>(fithStep, AutomatonDrawNodeStep(5, state5relations)));
        }
    };

} //Automaton
} //Algorithms

ADD_TEST(Algorithms::Automaton::AutomatonCStepsExecutorUT)
#include "AutomatonCStepsExecutorUT.moc"
