#include <QTest>
#include "TestCollector.h"

#include "Mocks/CControllerToolsetFactoryMock.h"
#include "Mocks/CPainterMock.h"
#include "../AlgorithmsModule/CController.h"

namespace Algorithms
{

    using namespace Window::Visualization;

    namespace
    {
        const auto createStringViewMock = [](const std::string& value)
        {
            std::function<std::string_view()> ret = [&value]() { return std::string_view(value); };
            return ret;
        };
    } //anonymous

    class CControllerUT: public QObject
    {
        Q_OBJECT

    private:

    private slots:

        void ControllerCorrectlyConstrucedWithFactory()
        {
            const std::string expectedInfo = "INFO";
            const std::string expectedName = "NAME";
            CControllerToolsetFactoryMock* factoryPrep = new CControllerToolsetFactoryMock();
            factoryPrep->m_createInfo = createStringViewMock(expectedInfo);
            factoryPrep->m_createName = createStringViewMock(expectedName);

            ControllerToolsetFactoryPtr mockFactory(factoryPrep);
            PainterPtr mockPainter = std::make_unique<CPainterMock>();

            ControllerPtr controller = std::make_unique<CController>(mockFactory, mockPainter);
            QCOMPARE(controller->getAlgorithmName(), expectedName);
            QCOMPARE(controller->getAlgorithmInfo(), expectedInfo);
        };
    };

} //Algorithms

ADD_TEST(Algorithms::CControllerUT)
#include "CControllerUT.moc"
