#include "TestCollector.h"

#include "../../AlgorithmsModule/BoyerMoore/IPainter.h"
#include "../../AlgorithmsModule/BoyerMoore/CControllerToolsetFactory.h"
#include "../../AlgorithmsModule/BoyerMoore/CStepsExecutor.h"

namespace Algorithms
{
namespace BoyerMoore
{

    using BoyerMoorePainter = Visualization::BoyerMoore::PainterPtr;
    using BoyerMooreToolsetFactory = CControllerToolsetFactory<BoyerMoorePainter>;
    using BoyerMooreStepsExecutor = CStepsExecutor<BoyerMoorePainter>;

    class BoyerMooreCControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT

    private:

        BoyerMooreToolsetFactory m_factory;

    private slots:

        void CreateInfoReturnsProperValue()
        {
            QCOMPARE(m_factory.createInfo(), BOYER_MOORE_INFO);
        }

        void CreateNameReturnsProperValue()
        {
            QCOMPARE(m_factory.createName(), BOYER_MOORE_NAME);
        }

        void CreateStepsExecutorCreatesProperObject()
        {
            const auto& stepsExecutor = m_factory.createStepsExecutor();
            QVERIFY(dynamic_cast<BoyerMooreStepsExecutor*>(stepsExecutor.get()) != nullptr);
        }
    };

} //BoyerMoore
} //Algorithms

ADD_TEST(Algorithms::BoyerMoore::BoyerMooreCControllerToolsetFactoryUT)
#include "BoyerMooreCControllerToolsetFactoryUT.moc"
