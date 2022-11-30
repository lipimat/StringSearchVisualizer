#include "CControllerToolsetFactory.h"
#include "CStepsExecutor.h"

namespace Algorithms
{
namespace Automaton
{

    std::string_view CControllerToolsetFactory::createName() const
    {
        return AUTOMATON_NAME;
    }

    std::string_view CControllerToolsetFactory::createInfo() const
    {
        return AUTOMATON_INFO;
    }

    StepsExecutorPtr CControllerToolsetFactory::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor>();
    }

     Visualization::PainterPtr CControllerToolsetFactory::createPainter(
            const Visualization::PainterFactoryPtr& painterFactory) const
    {
        assert(painterFactory != nullptr);
        return painterFactory->createAutomatonPainter();
    }

} //BoyerMoore
} //Algorithms
