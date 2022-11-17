#include "TestCollector.h"

#include "../../AlgorithmsModule/Steps/Constants.h"
#include "../../AlgorithmsModule/CController.h"
#include "Mocks/CControllerToolsetFactoryMock.h"
#include "Mocks/CPainterMock.h"
#include "Mocks/CStepsExecutorMock.h"
#include "Mocks/CPainterFactoryMock.h"

namespace Algorithms
{

    using namespace Visualization;

    namespace
    {
        const auto createStringViewMock = [](const std::string& value)
        {
            std::function<std::string_view()> ret = [&value]() { return std::string_view(value); };
            return ret;
        };

        const auto createStepsExecutorMock = [](std::unique_ptr<CStepsExecutorMock>& mock)
        {
            std::function<StepsExecutorPtr()> ret = [&mock]() { return std::make_unique<CStepsExecutorMock>(*mock.release()); };
            return ret;
        };

        const auto createCallableVoidWithTextsPairMock = [](int& called)
        {
            std::function<void(const TextsPair&)> ret = [&called](const TextsPair&) { called = 1; return; };
            return ret;
        };

        const auto createCleanWholeSceneMock = [](int& called)
        {
            std::function<void()> ret = [&called]() { called = 1; return; };
            return ret;
        };

        const auto createCalculateNextStepMock = [](int& called, const Steps::EState state)
        {
            std::function<Steps::EState()> ret = [&called, &state]() { called = 1; return state;};
            return ret;
        };

        const auto createPainterMock = [](std::unique_ptr<CPainterMock>& mock)
        {
            std::function<PainterPtr(const PainterFactoryPtr&)> ret =
                    [&mock](const PainterFactoryPtr&) { return std::make_unique<CPainterMock>(*mock.release()); };
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
            std::unique_ptr<CStepsExecutorMock> executorPrep = std::make_unique<CStepsExecutorMock>();
            std::unique_ptr<CPainterMock> painterPrep = std::make_unique<CPainterMock>();
            PainterFactoryPtr mockPainterFactory;

            const std::string expectedInfo = "INFO";
            const std::string expectedName = "NAME";
            std::unique_ptr<CControllerToolsetFactoryMock> factoryPrep = std::make_unique<CControllerToolsetFactoryMock>();
            factoryPrep->m_createInfo = createStringViewMock(expectedInfo);
            factoryPrep->m_createName = createStringViewMock(expectedName);
            factoryPrep->m_createStepsExecutor = createStepsExecutorMock(executorPrep);
            factoryPrep->m_createPainter = createPainterMock(painterPrep);
            ControllerToolsetFactoryPtr mockFactory(factoryPrep.release());

            CController controller(mockFactory, mockPainterFactory);
            QCOMPARE(controller.getAlgorithmName(), expectedName);
            QCOMPARE(controller.getAlgorithmInfo(), expectedInfo);
        }

        void ControllerInitializeSceneInitializesExecutorAndPainter()
        {
            int executorCalled = 0, painterCalled = 0;

            std::unique_ptr<CStepsExecutorMock> executorPrep = std::make_unique<CStepsExecutorMock>();
            executorPrep->m_initialize = createCallableVoidWithTextsPairMock(executorCalled);
            std::unique_ptr<CPainterMock> painterPrep = std::make_unique<CPainterMock>();
            painterPrep->m_drawBasicScene = createCallableVoidWithTextsPairMock(painterCalled);
            PainterFactoryPtr mockPainterFactory;

            const std::string expectedInfo = "INFO";
            const std::string expectedName = "NAME";
            std::unique_ptr<CControllerToolsetFactoryMock> factoryPrep = std::make_unique<CControllerToolsetFactoryMock>();
            factoryPrep->m_createInfo = createStringViewMock(expectedInfo);
            factoryPrep->m_createName = createStringViewMock(expectedName);
            factoryPrep->m_createStepsExecutor = createStepsExecutorMock(executorPrep);
            factoryPrep->m_createPainter = createPainterMock(painterPrep);
            ControllerToolsetFactoryPtr mockFactory(factoryPrep.release());

            CController controller(mockFactory, mockPainterFactory);
            controller.initializeScene({"",""});

            QCOMPARE(executorCalled, 1);
            QCOMPARE(painterCalled, 1);
        }

        void ControllerCleanScenceCallsPainter()
        {
            int painterCalled = 0;

            std::unique_ptr<CStepsExecutorMock> executorPrep = std::make_unique<CStepsExecutorMock>();
            std::unique_ptr<CPainterMock> painterPrep = std::make_unique<CPainterMock>();
            painterPrep->m_cleanWholeScene = createCleanWholeSceneMock(painterCalled);
            PainterFactoryPtr mockPainterFactory;

            const std::string expectedInfo = "INFO";
            const std::string expectedName = "NAME";
            std::unique_ptr<CControllerToolsetFactoryMock> factoryPrep = std::make_unique<CControllerToolsetFactoryMock>();
            factoryPrep->m_createInfo = createStringViewMock(expectedInfo);
            factoryPrep->m_createName = createStringViewMock(expectedName);
            factoryPrep->m_createStepsExecutor = createStepsExecutorMock(executorPrep);
            factoryPrep->m_createPainter = createPainterMock(painterPrep);
            ControllerToolsetFactoryPtr mockFactory(factoryPrep.release());

            CController controller(mockFactory, mockPainterFactory);
            controller.cleanScene();

            QCOMPARE(painterCalled, 1);
        }

        void ControllerNextStepReturnsFalseWhenAlgorithmFinished()
        {
            int executorCalled = 0;
            std::unique_ptr<CStepsExecutorMock> executorPrep = std::make_unique<CStepsExecutorMock>();
            executorPrep->m_calculateNextStep = createCalculateNextStepMock(executorCalled, Steps::EState::FINISHED);
            std::unique_ptr<CPainterMock> painterPrep = std::make_unique<CPainterMock>();
            PainterFactoryPtr mockPainterFactory;

            const std::string expectedInfo = "INFO";
            const std::string expectedName = "NAME";
            std::unique_ptr<CControllerToolsetFactoryMock> factoryPrep = std::make_unique<CControllerToolsetFactoryMock>();
            factoryPrep->m_createInfo = createStringViewMock(expectedInfo);
            factoryPrep->m_createName = createStringViewMock(expectedName);
            factoryPrep->m_createStepsExecutor = createStepsExecutorMock(executorPrep);
            factoryPrep->m_createPainter = createPainterMock(painterPrep);
            ControllerToolsetFactoryPtr mockFactory(factoryPrep.release());

            CController controller(mockFactory, mockPainterFactory);

            QCOMPARE(controller.nextStep(), false);
            QCOMPARE(executorCalled, 1);
        }

        void ControllerNextStepReturnsTrueWhenAlgorithmContinues()
        {
//            int executorCalled = 0;
//            std::unique_ptr<CStepsExecutorMock> executorPrep = std::make_unique<CStepsExecutorMock>();
//            executorPrep->m_calculateNextStep = createCalculateNextStepMock(executorCalled, Steps::EState::CONTINUE);
//            std::unique_ptr<CPainterMock> painterPrep = std::make_unique<CPainterMock>();
//            PainterFactoryPtr mockPainterFactory;

//            const std::string expectedInfo = "INFO";
//            const std::string expectedName = "NAME";
//            std::unique_ptr<CControllerToolsetFactoryMock> factoryPrep = std::make_unique<CControllerToolsetFactoryMock>();
//            factoryPrep->m_createInfo = createStringViewMock(expectedInfo);
//            factoryPrep->m_createName = createStringViewMock(expectedName);
//            factoryPrep->m_createStepsExecutor = createStepsExecutorMock(executorPrep);
//            factoryPrep->m_createPainter = createPainterMock(painterPrep);
//            ControllerToolsetFactoryPtr mockFactory(factoryPrep.release());

//            CController controller(mockFactory, mockPainterFactory);

//            QCOMPARE(controller.nextStep(), false);
//            QCOMPARE(executorCalled, 1);
        }
    };

} //Algorithms

ADD_TEST(Algorithms::CControllerUT)
#include "CControllerUT.moc"
