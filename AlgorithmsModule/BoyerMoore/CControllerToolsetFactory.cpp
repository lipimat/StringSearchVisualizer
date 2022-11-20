#include "CControllerToolsetFactory.h"
#include "CStepsExecutor.h"

namespace Algorithms
{
namespace BoyerMoore
{

    std::string_view CControllerToolsetFactory::createName() const
    {
        return BOYER_MOORE_NAME;
    }

    std::string_view CControllerToolsetFactory::createInfo() const
    {
        return BOYER_MOORE_INFO;
    }

    StepsExecutorPtr CControllerToolsetFactory::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor>();
    }

     Visualization::PainterPtr CControllerToolsetFactory::createPainter(
            const Visualization::PainterFactoryPtr& painterFactory) const
    {
        assert(painterFactory != nullptr);
        return painterFactory->createBruteForcePainter(); //TODO change to boyer moore painter
    }

} //BoyerMoore
} //Algorithms
