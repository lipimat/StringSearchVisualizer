#include "CControllerToolsetFactory.h"

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

} //BoyerMoore
} //Algorithms
