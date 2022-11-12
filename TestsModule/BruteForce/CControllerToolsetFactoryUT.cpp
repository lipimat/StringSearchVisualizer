#include <QTest>
#include "TestCollector.h"

#include "../AlgorithmsModule/BruteForce/CControllerToolsetFactory.h"
#include "../AlgorithmsModule/BruteForce/CStepsExecutor.h"

namespace Algorithms
{
namespace BruteForce
{

    class CControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT

    private:

        CControllerToolsetFactory m_factory;

    private slots:

        void CreateInfoReturnsProperValue()
        {
            QCOMPARE(m_factory.createInfo(), BRUTE_FORCE_INFO);
        };

        void CreateNameReturnsProperValue()
        {
            QCOMPARE(m_factory.createName(), BRUTE_FORCE_NAME);
        }

        void CreateStepsExecutorCreatesProperObject()
        {
            const auto& stepsExecutor = m_factory.createStepsExecutor();
            QVERIFY(dynamic_cast<CStepsExecutor*>(stepsExecutor.get()) != nullptr);
        }

    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::CControllerToolsetFactoryUT)
#include "CControllerToolsetFactoryUT.moc"
