#include "TestCollector.h"

#include "../../AlgorithmsModule/BoyerMoore/CControllerToolsetFactory.h"

namespace Algorithms
{
namespace BoyerMoore
{

    class BoyerMooreCControllerToolsetFactoryUT: public QObject
    {
        Q_OBJECT

    private:

        CControllerToolsetFactory m_factory;

    private slots:

        void CreateInfoReturnsProperValue()
        {
            QCOMPARE(m_factory.createInfo(), BOYER_MOORE_INFO);
        }

        void CreateNameReturnsProperValue()
        {
            QCOMPARE(m_factory.createName(), BOYER_MOORE_NAME);
        }
    };

} //BoyerMoore
} //Algorithms

ADD_TEST(Algorithms::BoyerMoore::BoyerMooreCControllerToolsetFactoryUT)
#include "BoyerMooreCControllerToolsetFactoryUT.moc"
