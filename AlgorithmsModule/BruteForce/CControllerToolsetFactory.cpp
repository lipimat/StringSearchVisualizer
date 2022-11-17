#include "CControllerToolsetFactory.h"

#include "CStepsExecutor.h"

namespace Algorithms
{
namespace BruteForce
{

    std::string_view CControllerToolsetFactory::createName() const
    {
        return BRUTE_FORCE_NAME;
    }

    std::string_view CControllerToolsetFactory::createInfo() const
    {
        return BRUTE_FORCE_INFO;
    }

    StepsExecutorPtr CControllerToolsetFactory::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor>();
    }

     Visualization::PainterPtr CControllerToolsetFactory::createPainter(
            const Visualization::PainterFactoryPtr& painterFactory) const
    {
        assert(painterFactory);
        return painterFactory->createBruteForcePainter();
    }

} //BruteForce
} //Algorithms
