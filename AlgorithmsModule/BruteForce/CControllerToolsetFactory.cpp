#include "CControllerToolsetFactory.h"

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

} //BruteForce
} //Algorithms
