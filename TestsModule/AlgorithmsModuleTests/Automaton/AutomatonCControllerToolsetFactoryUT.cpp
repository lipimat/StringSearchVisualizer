#include "TestCollector.h"

#include "../../AlgorithmsModule/Automaton/CControllerToolsetFactory.h"
#include "../../AlgorithmsModule/Automaton/CStepsExecutor.h"

namespace Algorithms
{
namespace Automaton
{

    class AutomatonCControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT

    private:

        CControllerToolsetFactory m_factory;

    private slots:

        void CreateInfoReturnsProperValue()
        {
            QCOMPARE(m_factory.createInfo(), AUTOMATON_INFO);
        }

        void CreateNameReturnsProperValue()
        {
            QCOMPARE(m_factory.createName(), AUTOMATON_NAME);
        }

        void CreateStepsExecutorCreatesProperObject()
        {
            const auto& stepsExecutor = m_factory.createStepsExecutor();
            QVERIFY(dynamic_cast<CStepsExecutor*>(stepsExecutor.get()) != nullptr);
        }

    };

} //Automaton
} //Algorithms

ADD_TEST(Algorithms::Automaton::AutomatonCControllerToolsetFactoryUT)
#include "AutomatonCControllerToolsetFactoryUT.moc"
