#include "CController.h"
#include "SupportedAlgorithmsAlphabet.h"
#include "Automaton/IPainter.h"
#include "BoyerMoore/IPainter.h"
#include "BruteForce/IPainter.h"
#include "Steps/IStep.h"
#include "Steps/Constants.h"

namespace Algorithms
{
    template<class Painter>
    template<class PainterImpl>
    class CController<Painter>::Impl
    {
    public:

        Impl(const ControllerToolsetFactoryPtr<Painter>&, PainterImpl&&);
        inline const std::string& getAlgorithmName() const { return m_algorithmName; };
        inline const std::string& getAlgorithmInfo() const { return m_algorithmInfo; };
        inline const PainterImpl& getPainter() const { return m_painter; };
        inline const StepsExecutorPtr<Painter>& getExecutor() const { return m_executor; };

        ~Impl() = default;

    private:
        const std::string m_algorithmName;
        const std::string m_algorithmInfo;

        PainterImpl m_painter;
        StepsExecutorPtr<Painter> m_executor;
    };

    template<class Painter>
    template<class PainterImpl>
    CController<Painter>::Impl<PainterImpl>::Impl(const ControllerToolsetFactoryPtr<Painter>& toolsetFactory, PainterImpl&& painter) :
        m_algorithmName(toolsetFactory->createName()),
        m_algorithmInfo(toolsetFactory->createInfo()),
        m_executor(toolsetFactory->createStepsExecutor()),
        m_painter(std::move(painter))
    {
        assert(m_painter != nullptr);
        assert(m_executor != nullptr);
    }

    template<class Painter>
    CController<Painter>::CController(const ControllerToolsetFactoryPtr<Painter>& toolsetFactory, Painter&& painter) :
        m_impl(std::make_unique<CController<Painter>::Impl<Painter>>(toolsetFactory, std::move(painter)))
    {
        assert(m_impl != nullptr);
    }

    template<class Painter>
    const std::string& CController<Painter>::getAlgorithmName() const
    {
        return m_impl->getAlgorithmName();
    }

    template<class Painter>
    const std::string& CController<Painter>::getAlgorithmInfo() const
    {
        return m_impl->getAlgorithmInfo();
    }

    template<class Painter>
    void CController<Painter>::initializeScene(const TextsPair& userTexts) const
    {
        if(userTexts.first.empty() || userTexts.second.empty())
            throw std::runtime_error("Some texts are empty! Please fill in both texts!");
        else
        {
            std::regex baseRegex("^[" + std::string(Algorithms::SUPPORTED_ALPHABET) + "]+$");
            std::smatch baseMatch;
            if(!std::regex_match(userTexts.first, baseMatch, baseRegex) || !std::regex_match(userTexts.second, baseMatch, baseRegex))
                throw std::runtime_error("Some texts are not valid with supported alphabet! Please correct them!");
        }
        const auto& painter = m_impl->getPainter();
        const auto& stepsExecutor = m_impl->getExecutor();
        painter->drawBasicScene(userTexts);
        stepsExecutor->initialize(userTexts);
    }

    template<class Painter>
    void CController<Painter>::cleanScene() const
    {
        const auto& painter = m_impl->getPainter();
        painter->cleanWholeScene();
    }

    template<class Painter>
    bool CController<Painter>::nextStep() const
    {
        const auto& stepsExecutor = m_impl->getExecutor();
        const auto algorithmProgress = stepsExecutor->calculateNextStep();

        const auto isAlgorithmInProgress = algorithmProgress == Steps::EAlgorithmState::CONTINUE;
        const auto isAlgorithmFinished = !isAlgorithmInProgress;
        if(isAlgorithmInProgress)
        {
            const auto& currentStep = stepsExecutor->getCurrentStep();
            assert(currentStep != nullptr);
            const auto& painter = m_impl->getPainter();
            currentStep->accept(painter);
        }
        else if(isAlgorithmFinished)
        {
            const auto& painter = m_impl->getPainter();
            painter->finishScene(stepsExecutor->getFoundPatternIndices());
        }
        return isAlgorithmInProgress;
    }

    template<class Painter>
    CController<Painter>::~CController() = default;

    template class CController<Visualization::BruteForce::PainterPtr>;
    template class CController<Visualization::BoyerMoore::PainterPtr>;
    template class CController<Visualization::Automaton::PainterPtr>;

} // Algorithms
