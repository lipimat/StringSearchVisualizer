#include "CControllerCreator.h"
#include "CControllerToolsetFactory.h"
#include "IPainter.h"
#include "../CController.h"
#include "../IPainterFactory.h"

namespace
{
using BruteForcePainter = Visualization::BruteForce::PainterPtr;
using BruteForceToolsetFactory = Algorithms::BruteForce::CControllerToolsetFactory<BruteForcePainter>;
using BruteForceController = Algorithms::CController<BruteForcePainter>;
}

namespace Algorithms
{
namespace BruteForce
{
    ControllerPtr CControllerCreator::createController(const Visualization::PainterFactoryPtr& painterFactory) const
    {
        return std::make_unique<BruteForceController>(std::make_unique<BruteForceToolsetFactory>(), painterFactory->createBruteForcePainter());
    };

} // BruteForce
} // Algorithms
