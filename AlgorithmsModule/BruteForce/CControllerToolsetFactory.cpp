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

    std::unique_ptr<IStepsExecutor> CControllerToolsetFactory::createStepsExecutor() const
    {
        return std::make_unique<CStepsExecutor>();
    }

} //BruteForce
} //Algorithms
