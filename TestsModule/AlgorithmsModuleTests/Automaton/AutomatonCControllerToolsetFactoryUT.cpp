#include "TestCollector.h"

#include "../../AlgorithmsModule/Automaton/CControllerToolsetFactory.h"
#include "../../AlgorithmsModule/Automaton/CStepsExecutor.h"
#include "../../AlgorithmsModule/Automaton/IPainter.h"

namespace Algorithms
{
namespace Automaton
{

    using AutomatonPainter = Visualization::Automaton::PainterPtr;
    using AutomatonToolsetFactory = CControllerToolsetFactory<AutomatonPainter>;
    using AutomatonStepsExecutor = CStepsExecutor<AutomatonPainter>;

    class AutomatonCControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT

    private:

        AutomatonToolsetFactory m_factory;

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
            QVERIFY(dynamic_cast<AutomatonStepsExecutor*>(stepsExecutor.get()) != nullptr);
        }

    };

} //Automaton
} //Algorithms

ADD_TEST(Algorithms::Automaton::AutomatonCControllerToolsetFactoryUT)
#include "AutomatonCControllerToolsetFactoryUT.moc"
