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

    private:

        CControllerToolsetFactory m_factory;

    private slots:

        void CreateInfoReturnsProperValue()
        {
            QVERIFY(m_factory.createInfo() == BRUTE_FORCE_INFO);
        };

        void CreateNameReturnsProperValue()
        {
            QVERIFY(m_factory.createName() == BRUTE_FORCE_NAME);
        }

    };

} //BruteForce
} //Algorithms

ADD_TEST(Algorithms::BruteForce::CControllerToolsetFactoryUT)
#include "CControllerToolsetFactoryUT.moc"
