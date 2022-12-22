#include "CControllerCreator.h"
#include "CControllerToolsetFactory.h"
#include "IPainter.h"
#include "../CController.h"
#include "../IPainterFactory.h"

namespace
{
using BoyerMoorePainter = Visualization::BoyerMoore::PainterPtr;
using BoyerMooreToolsetFactory = Algorithms::BoyerMoore::CControllerToolsetFactory<BoyerMoorePainter>;
using BoyerMooreController = Algorithms::CController<BoyerMoorePainter>;
}

namespace Algorithms
{
namespace BoyerMoore
{
    ControllerPtr CControllerCreator::createController(const Visualization::PainterFactoryPtr& painterFactory) const
    {
        return std::make_unique<BoyerMooreController>(std::make_unique<BoyerMooreToolsetFactory>(), painterFactory->createBoyerMoorePainter());
    };

} // BoyerMoore
} // Algorithms
