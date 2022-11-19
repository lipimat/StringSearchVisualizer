#include "TestCollector.h"

#include "../../AlgorithmsModule/Steps/Constants.h"
#include "../../AlgorithmsModule/CController.h"
#include "Mocks/CControllerToolsetFactoryMock.h"
#include "Mocks/CPainterMock.h"
#include "Mocks/CStepsExecutorMock.h"
#include "Mocks/CStepMock.h"

namespace Algorithms
{

    using namespace Visualization;

    class CControllerUT: public QObject
    {
        Q_OBJECT

    private:

        const std::string m_expectedName = "NAME";
        const std::string m_expectedInfo = "INFO";

        std::unique_ptr<CStepsExecutorMock> m_stepsExecutorMock;
        std::unique_ptr<CPainterMock> m_painterMock;
        std::unique_ptr<CControllerToolsetFactoryMock> m_toolsetFactoryMock;

        const CController createController()
        {
            m_toolsetFactoryMock->m_createInfo = [&]() { return std::string_view(m_expectedInfo); };
            m_toolsetFactoryMock->m_createName = [&]() { return std::string_view(m_expectedName); };
            m_toolsetFactoryMock->m_createStepsExecutor = [&]() { return std::make_unique<CStepsExecutorMock>(*m_stepsExecutorMock.release()); };
            m_toolsetFactoryMock->m_createPainter = [&](const PainterFactoryPtr&) { return std::make_unique<CPainterMock>(*m_painterMock.release()); };

            ControllerToolsetFactoryPtr m_toolsetFactory(m_toolsetFactoryMock.release());
            PainterFactoryPtr m_painterFactory;
            return CController(m_toolsetFactory, m_painterFactory);
        }

    private slots:

        void init()
        {
            // reset mocks after each method
            m_stepsExecutorMock = std::make_unique<CStepsExecutorMock>();
            m_painterMock = std::make_unique<CPainterMock>();
            m_toolsetFactoryMock = std::make_unique<CControllerToolsetFactoryMock>();
        }

        void ControllerCorrectlyConstrucedWithFactory()
        {
            const auto& controller = createController();
            QCOMPARE(controller.getAlgorithmName(), m_expectedName);
            QCOMPARE(controller.getAlgorithmInfo(), m_expectedInfo);
        }

        void ControllerInitializeSceneInitializesExecutorAndPainter()
        {
            int executorInitializeCalled = 0, painterDrawBasicSceneCalled = 0;

            m_stepsExecutorMock->m_initialize = [&](const TextsPair&) { executorInitializeCalled = 1; return; };
            m_painterMock->m_drawBasicScene = [&](const TextsPair&) { painterDrawBasicSceneCalled = 1; return; }; //ugly but cannot do template lambda (look for it)

            const auto& controller = createController();
            controller.initializeScene({"",""});
            QCOMPARE(executorInitializeCalled, 1);
            QCOMPARE(painterDrawBasicSceneCalled, 1);
        }

        void ControllerCleanScenceCallsPainter()
        {
            int painterCleanWholeSceneCalled = 0;

            m_painterMock->m_cleanWholeScene = [&]() { painterCleanWholeSceneCalled = 1; return; };
            const auto& controller = createController();
            controller.cleanScene();

            QCOMPARE(painterCleanWholeSceneCalled, 1);
        }

        void ControllerNextStepReturnsFalseWhenAlgorithmFinished()
        {
            int executorCalculateNextStepCalled = 0;

            m_stepsExecutorMock->m_calculateNextStep = [&]() { executorCalculateNextStepCalled = 1; return Steps::EAlgorithmState::FINISHED; };
            const auto& controller = createController();

            QCOMPARE(controller.nextStep(), false);
            QCOMPARE(executorCalculateNextStepCalled, 1);
        }

        void ControllerNextStepReturnsTrueWhenAlgorithmContinues()
        {
            int executorCalculateNextStepCalled = 0, getCurrentStepCalled = 0, stepAcceptPainterCalled = 0;

            auto stepMock = std::make_unique<Steps::CStepMock>();
            stepMock->m_accept = [&](const Visualization::PainterPtr&)
                { getCurrentStepCalled = 1; /*it was called earlier*/ stepAcceptPainterCalled = 1; return; };
            m_stepsExecutorMock->m_calculateNextStep = [&]() { executorCalculateNextStepCalled = 1; return Steps::EAlgorithmState::CONTINUE; };
            m_stepsExecutorMock->m_getCurrentStep = std::make_unique<Steps::CStepMock>(*stepMock.release());
            const auto& controller = createController();

            QCOMPARE(controller.nextStep(), true);
            QCOMPARE(executorCalculateNextStepCalled, 1);
            QCOMPARE(getCurrentStepCalled, 1);
            QCOMPARE(stepAcceptPainterCalled, 1);
        }
    };

} //Algorithms

ADD_TEST(Algorithms::CControllerUT)
#include "CControllerUT.moc"
