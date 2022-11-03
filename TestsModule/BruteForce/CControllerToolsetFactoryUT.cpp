#include <QTest>
#include "TestCollector.h"

#include "../AlgorithmsModule/BruteForce/CControllerToolsetFactory.h"

namespace Algorithms
{
namespace BruteForce
{

    class CControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT
    private slots:

        void CreateInfoReturnsProperValue()
        {
            CControllerToolsetFactory factory;
            QVERIFY(factory.createInfo() == BRUTE_FORCE_INFO);
        };

    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::CControllerToolsetFactoryUT)
#include "CControllerToolsetFactoryUT.moc"
