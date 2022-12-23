#include "TestCollector.h"

#include "../../AlgorithmsModule/BruteForce/IPainter.h"
#include "../../AlgorithmsModule/BruteForce/CControllerToolsetFactory.h"
#include "../../AlgorithmsModule/BruteForce/CStepsExecutor.h"

namespace Algorithms
{
namespace BruteForce
{

    using BruteForcePainter = Visualization::BruteForce::PainterPtr;
    using BruteForceToolsetFactory = CControllerToolsetFactory<BruteForcePainter>;
    using BruteForceStepsExecutor = CStepsExecutor<BruteForcePainter>;

    class BruteForceCControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT

    private:

        BruteForceToolsetFactory m_factory;

    private slots:

        void CreateInfoReturnsProperValue()
        {
            QCOMPARE(m_factory.createInfo(), BRUTE_FORCE_INFO);
        }

        void CreateNameReturnsProperValue()
        {
            QCOMPARE(m_factory.createName(), BRUTE_FORCE_NAME);
        }

        void CreateStepsExecutorCreatesProperObject()
        {
            const auto& stepsExecutor = m_factory.createStepsExecutor();
            QVERIFY(dynamic_cast<BruteForceStepsExecutor*>(stepsExecutor.get()) != nullptr);
        }

    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::BruteForceCControllerToolsetFactoryUT)
#include "BruteForceCControllerToolsetFactoryUT.moc"
