#include <QTest>
#include "TestCollector.h"

#include "../AlgorithmsModule/CController.h"
#include "../AlgorithmsModule/SupportedAlgorithmsToolsets.h"

namespace Algorithms
{

    class CControllerUT: public QObject
    {
        Q_OBJECT

    private:

        std::vector<CController> controllers;

    private slots:

        void initTestCase()
        {
            for(const auto& factory : toolsetFactories)
            {
                controllers.push_back(CController(factory.get()));
            }
        }

        void GetAlgorithmNameReturnsNonEmptyValue()
        {
            for(const auto& controller : controllers)
            {
                const auto isNameNonEmpty = !controller.getAlgorithmName().empty();
                QVERIFY(isNameNonEmpty);
            }
        }

        void GetAlgorithmInfoReturnsNonEmptyValue()
        {
            for(const auto& controller : controllers)
            {
                const auto isInfoNonEmpty = !controller.getAlgorithmInfo().empty();
                QVERIFY(isInfoNonEmpty);
            }
        }

    };

} //Algorithms

ADD_TEST(Algorithms::CControllerUT)
#include "CControllerUT.moc"
